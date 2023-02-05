from sage.all import *

import ctypes
from tqdm import trange

# RNG-related -------------------------------------------------------------------------------------
import arc4random
class RandomData(ctypes.Structure):
    _fields_ = [
        ('fptr', ctypes.POINTER(ctypes.c_int32)),
        ('rptr', ctypes.POINTER(ctypes.c_int32)),
        ('state', ctypes.POINTER(ctypes.c_int32)),
        ('rand_type', ctypes.c_int),
        ('rand_deg', ctypes.c_int),
        ('rand_sep', ctypes.c_int),
        ('end_ptr', ctypes.POINTER(ctypes.c_int32)),
    ]
lib = ctypes.cdll.LoadLibrary("libc.so.6")
lib.initstate_r.argtypes = [
    ctypes.c_uint,
    ctypes.c_char_p,
    ctypes.c_size_t,
    ctypes.POINTER(RandomData)
]

# Curve 25519 -------------------------------------------------------------------------------------
bytes_to_long = lambda x: int.from_bytes(x, 'little')
long_to_bytes = lambda x: int(x).to_bytes(32, 'little')

p = 0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffed
K = GF(p)
A = K(0x76d06)
B = K(0x01)
E = EllipticCurve(K, ((3 - A**2)/(3 * B**2), (2 * A**3 - 9 * A)/(27 * B**3)))
def to_weierstrass(x, y):
	return (x/B + A/(3*B), y/B)
def to_montgomery(u, v):
	return (B * (u - A/(3*B)), B*v)
G = E(*to_weierstrass(K(0x09), K(0x20ae19a1b8a086b4e01edd2c7748d14c923d4d7e6d7c61b229e9c5a27eced3d9)))
E.set_order(0x1000000000000000000000000000000014def9dea2f79cd65812631a5cf5d3ed * 0x08)

# -------------------------------------------------------------------------------------------------

def getentropy(time, pid):
    rv = []

    state = ctypes.create_string_buffer(int(32))
    rdata = RandomData()
    x = ctypes.c_int()

    rdata.state = None
    lib.initstate_r(time ^ pid, state, ctypes.sizeof(state), ctypes.pointer(rdata))
    for _ in range(40):
        lib.random_r(ctypes.pointer(rdata), ctypes.byref(x))
        rv.append(x.value & 0xff)
    return bytes(rv)

def find_private_key(client_pub, time):
    # they would start at 0, but we can skip to the answer
    for p in trange(14690, 1<<22, desc='finding private key'):
        for t in range(time - 1, time + 1):
            entropy = getentropy(t, p)
            rng = arc4random.RNG(entropy)
            rng.rs_random_buf(64) # 48 for seed_rng, 16 for kex_send_kexinit
            client_priv = bytearray(rng.rs_random_buf(32))
            client_priv[0] &= 248
            client_priv[31] &= 127
            client_priv[31] |= 64
            client_priv = bytes_to_long(client_priv)
            test_pub = client_priv * G
            test_pub = to_montgomery(test_pub[0], test_pub[1])[0]
            if test_pub == client_pub:
                return client_priv
    raise RuntimeError('no private key found :(')

def find_shared_secret(client_pub, server_pub, time):
    client_pub = bytes_to_long(client_pub)
    server_pub = bytes_to_long(server_pub)
    client_priv = find_private_key(client_pub, time)
    server_pub_point = E.lift_x(to_weierstrass(server_pub, 0)[0])
    shared_secret = client_priv * server_pub_point
    shared_secret = to_montgomery(shared_secret[0], shared_secret[1])[0]
    return long_to_bytes(shared_secret)
