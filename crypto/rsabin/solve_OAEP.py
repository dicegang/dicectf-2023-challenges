from Crypto.Util.number import getPrime, long_to_bytes, bytes_to_long
from sage.all import *
from pwn import *
from nth_root import nth_root

from Crypto.PublicKey import RSA
import ireland_PKCS1OAEP

"""
Note:
the point of this challenge is that Sage's nth_root functionality attempts to get a provable multiplicative generator for Zmod(p-1) by first factoring p-1. This is hella slow, for no good reason. But just picking a random element works pretty well, especially if you prune it by removing any small factors of p-1.

The source code for Sage's nth_root even says:
# the following may eventually be improved to not need a multiplicative generator.
"""

def encrypt(m):
    r.recvuntil(b"(EDF) >")
    r.sendline(b"E")
    r.recvuntil(b" > ")
    r.sendline(str(m).encode())
    c = r.recvline()
    c = int(c.decode())
    return c

def decrypt(c):
    r.recvuntil(b"(EDF) >")
    r.sendline(b"D")
    r.recvuntil(b" > ")
    r.sendline(str(c).encode())
    c = r.recvline()
    m = int(c.decode())
    return m

def encrypt_flag():
    r.recvuntil(b"(EDF) >")
    r.sendline(b"F")
    c = r.recvline()
    c = int(c.decode())
    return c


############################################

e = 17
smooth_factors = prod(primes_first_n(1000))**10

context.log_level = 'error'

"""
reconnect until get malformed N
"""

while True:
    print("reconnecting")
    # r = process(["/opt/sagemath-9.2/src/bin/sage", "challenge.py"])
    r = remote("mc.ax", 31370)

    m = pow(2, 100)
    c = encrypt(m)
    m1 = decrypt(c)

    if m != m1:
        break
    else:
        r.close()


# will be used later in CCA gcd attack
m_original = m
m_returned = m1

############################################

"""
recover N
"""

m1 = pow(2, 100)
c1 = encrypt(m1)

m2 = pow(2, 100) + 0x1337
c2 = encrypt(m2)

d1 = encrypt(m1) - m1**e
d2 = encrypt(m2) - m2**e
N = gcd(d1, d2)

N //= gcd(N, smooth_factors)

print("N = ", N)

############################################

"""
recover p using CCA gcd attack on Rabin cryptosystem
"""

p = gcd(m_original - m_returned, N)
p //= gcd(p, smooth_factors)
print("p = ", p)
q = N//p
print("q = ", q)

############################################

"""
decrypt flag
"""
N = int(N)

key = RSA.construct((N, e))
cipher = ireland_PKCS1OAEP.new(key)

c = encrypt_flag()
mp = nth_root(c, p, e, all=True)
mq = nth_root(c, q, e, all=True)

for mp1 in mp:
    for mq1 in mq:
        m = int(CRT([ZZ(mp1), ZZ(mq1)], [p, q]))
        try:
            m = cipher.decode(m)
        except:
            continue
        print(m.decode())


