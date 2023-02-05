# Solves one iteration, requires manually inputting stuff
from Crypto.Cipher import PKCS1_OAEP
from Crypto.PublicKey import RSA
from Crypto.Hash import SHA256
from Crypto.Util.strxor import strxor

n0 = int(input("pk0: "))
n1 = int(input("pk1: "))

pk0 = PKCS1_OAEP.new(RSA.construct((n0, 65537)), hashAlgo=SHA256)
pk1 = PKCS1_OAEP.new(RSA.construct((n1, 65537)), hashAlgo=SHA256)

ct = bytes.fromhex(input("ct: ").strip())
ct0 = ct[:256]
ct1 = ct[256:]

print("Decrypt for r: ", ct0.hex() + pk1.encrypt(b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00').hex())

print("Decrypt for r': ", pk0.encrypt(b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00').hex() + ct1.hex())

r = bytes.fromhex(input("r: ").strip())
r_prime = bytes.fromhex(input("r': ").strip())

print("msg: ", strxor(r, r_prime).hex())
