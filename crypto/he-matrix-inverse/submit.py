from pwn import *
import subprocess

r = remote("mc.ax", 30917)

pow_intro = r.recvuntil(b"proof of work: ")
pow_cmd = r.recvline().strip()
pow_outro = r.recvuntil(b"solution: ")
pow_answer = subprocess.check_output(pow_cmd, shell=True)
r.send(pow_answer)

msg = r.recv().strip().decode()
print(msg)

with open("sol.ctxt", "rb") as f:
	data = f.read()

r.sendline(data.hex().encode())

sleep(1)

msg = r.recv().strip().decode()
print(msg)