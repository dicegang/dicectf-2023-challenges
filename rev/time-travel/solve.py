import struct

import numpy as np

with open("handout/input.bin", "rb") as enc_f:
    enc = enc_f.read()

offset = 0
SIZE = struct.unpack_from("<i", enc, offset)[0]
offset += 4

for i, c in enumerate(range(64)):
    vals = []
    for _ in range(SIZE * SIZE):
        vals.append(struct.unpack_from("<q", enc, offset)[0])
        offset += 8
    det = round(np.linalg.det(np.asarray(vals, dtype=np.int64).reshape((SIZE, SIZE))))

    flag_diff = struct.unpack_from("<q", enc, offset)[0]

    offset += 8

    print(chr(flag_diff - det + i), end='')
print()
