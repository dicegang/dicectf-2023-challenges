# zip -r dice.zip challenge.qasm stabilizer.py solve.py

from qiskit import QuantumCircuit
from qiskit.quantum_info import Clifford
import random
import copy
import time
from Crypto.Util.number import long_to_bytes, bytes_to_long

###########################################################

n = 400

with open("flag.txt", "rb") as f:
    flag = f.read()

print(len(flag) * 8)
flag = bytes_to_long(flag)

flag_bits = f"{flag:0{n}b}"
flag_bits = flag_bits[::-1]
assert len(flag_bits) <= n

m = 10000
qc = QuantumCircuit(n)

for gate_num in range(m):
    if random.randint(0,1):
        f = random.choice([qc.h, qc.x, qc.y, qc.z, qc.s, qc.sdg])
        i = random.choice(range(n))
        f(i)
    else:
        f = qc.cx
        i = random.sample(range(n), 2)
        f(*i)
        

qc2 = qc.inverse()
for i in range(n):
    if flag_bits[i] == "1":
        print(i)
        qc2.x(i)


start_time = time.time()
cliff = Clifford(qc2)
qc2_obf = cliff.to_circuit()
end_time = time.time()

print("time = {:.01f} s".format(end_time - start_time))

qc_final = qc.compose(qc2_obf)

###########################################################

s = qc_final.qasm()
with open("challenge.qasm", "w") as f:
    f.write(s)
    

