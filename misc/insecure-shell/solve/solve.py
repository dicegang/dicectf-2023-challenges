import hashlib
import io
import struct
import sys

from Crypto.Cipher import ChaCha20


def sha256(s):
    return hashlib.sha256(s).digest()

import capture


def bignum(s):
    if s[0] & 0x80 != 0:
        return b'\x00' + s
    return s
p32 = lambda x: struct.pack('>I', x)
p64 = lambda x: struct.pack('>Q', x)
u32 = lambda x: struct.unpack('>I', x)[0]
u64 = lambda x: struct.unpack('>Q', x)[0]
def pack_string(s):
    return p32(len(s)) + s

from getsecret import find_shared_secret

K = find_shared_secret(capture.client_pub, capture.server_pub, capture.timestamp)
K = pack_string(bignum(K))
print('K', K.hex())

buffer = b''.join([
    pack_string(capture.client_version),
    pack_string(capture.server_version),
    pack_string(b'\x14' + capture.client_kexinit),
    pack_string(b'\x14' + capture.server_kexinit),
    pack_string(capture.server_host_key),
    pack_string(capture.client_pub),
    pack_string(capture.server_pub),
    K,
])

H = sha256(buffer)
print('H', H.hex())

def derive_key(c, need):
    Kn = sha256(K + H + bytes([c]) + H)
    mdsz = len(Kn)
    have = mdsz
    while need > have:
        Kn += sha256(K + H + Kn)
        have += mdsz
    return Kn[:need]

def print_packet(packet):
    stream = io.BytesIO(packet)
    stream.read(1)
    if stream.read(1)[0] == 0x5e:
        stream.read(4)
        size = u32(stream.read(4))
        sys.stdout.buffer.write(stream.read(size))
        sys.stdout.flush()

server_key = derive_key(0x44, 64)
k2, k1 = server_key[:32], server_key[32:]
seq_num = 3
while True:
    try:
        cipher1 = ChaCha20.new(key=k1, nonce=p64(seq_num))
        size = u32(cipher1.decrypt(capture.server_stream.read(4)))
        cipher2 = ChaCha20.new(key=k2, nonce=p64(seq_num))
        cipher2.seek(64)
        packet = cipher2.decrypt(capture.server_stream.read(size))
        print_packet(packet)
        capture.server_stream.read(16)
        seq_num += 1
    except struct.error:
        break
