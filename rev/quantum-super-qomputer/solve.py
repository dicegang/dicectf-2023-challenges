from qiskit import QuantumCircuit, transpile
from qiskit.providers.aer import AerSimulator
from Crypto.Util.number import long_to_bytes, bytes_to_long

circ = QuantumCircuit.from_qasm_file("challenge.qasm")
circ.measure_all()

stabilizer_simulator = AerSimulator(method='stabilizer')

# Transpile circuit for backend
tcirc = transpile(circ, stabilizer_simulator)

stabilizer_result = stabilizer_simulator.run(tcirc, shots=1).result()

res = stabilizer_result.get_counts()
flag = list(res.keys())[0]

flag = int(flag, 2)
flag = long_to_bytes(flag)
print(flag)
