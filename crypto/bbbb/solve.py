from pwn import *
import random

targete = 11
period = 5
connections = 0

while True:
    connections += 1
    s = remote("localhost", 1005, level="debug")
    s.recvuntil(b"b=")
    b = int(s.recvline())
    s.recvuntil(b"p=")
    p = int(s.recvline())
    if (p - 1) % period == 0:
        while True:
            a = pow(random.randrange(1, p), p//period, p)
            rng = lambda x: (a*x + b) % p
            seeds = [targete]
            for _ in range(period - 1):
                seeds.append(rng(seeds[-1]))
            if rng(seeds[-1]) == targete:
                break
        s.sendlineafter(b"b[a]ckdoor!!:", str(a))
        for seed in seeds:
            s.sendlineafter(b"seed:", str(seed), timeout=1)
        cts = []
        data = s.recvall().decode().split("[+] Public Key:\n")
        for cipher in data[1:]:
            cipher = cipher.splitlines()
            n = int(cipher[0].split("=")[1])
            e = int(cipher[1].split("=")[1])
            r = bytes.fromhex(cipher[2].split("=")[1][1:-1])
            c = int(cipher[3].split(":")[1])
            cts.append((n, e, c, r))
        print(cts)
        if all(ct[1] == targete for ct in cts):
            break
    s.close()

print(f"took {connections} tries...")
# from experiments, around 35 average?