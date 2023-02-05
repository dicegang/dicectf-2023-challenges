import struct

import numpy as np

with open("./flag.txt") as flag_file:
    flag = flag_file.read().strip()

SIZE = 18

output = b""
output += struct.pack("<i", SIZE)

for i, c in enumerate(flag):
    while True:
        matrix = np.random.randint(0, 2, size=(SIZE, SIZE), dtype=np.int64)
        det = int(round(np.linalg.det(matrix)))

        if det != 0:
            break

    print(det, end=', ')

    for val in matrix.reshape((-1,)):
        output += struct.pack("<q", val)
    output += struct.pack("<q", ord(c) + det - i)
print()

with open("./handout/input.bin", "wb") as output_file:
    output_file.write(output)
