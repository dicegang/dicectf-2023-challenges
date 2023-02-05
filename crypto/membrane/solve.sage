import numpy as np
import copy
from tqdm import tqdm

# dimension
n = 512
# number of public key samples
m = n + 100
# plaintext modulus
p = 257
# ciphertext modulus
q = 1048583

V = VectorSpace(GF(q), n)

with np.load("data.npz") as f:
    pk_A = f["pk_A"]
    pk_b = f["pk_b"]
    encrypt_A = f["encrypt_A"]
    encrypt_b = f["encrypt_b"]

pk_A = Matrix(GF(q), pk_A)
pk_b = vector(GF(q), pk_b)

encrypt_A = Matrix(GF(q), encrypt_A)
encrypt_b = vector(GF(q), encrypt_b)


def solve(A, b):

    c0 = pk_A.solve_left(A)
    K = pk_A.left_kernel()

    """
    make c0 have zeros for the first (m-n) entries
    I think you could also adjust the lattice scale factor for c0,
    we're basically doing a CVP instance
    """
    for i,v in zip(c0, K.basis()):
        c0 -= i * v


    """
    looking for low-weighted combinations of c0 + the kernel vectors
    to produce a low-weighted vector

    only use the first 130 entries of the lattice when searching for short linear combinations.
    This lets us use a smaller lattice
    """

    d = len(K.basis())
    mc = d + 30

    M = []
    v = c0[:mc]
    pad = [0] * (d + 1)
    pad[-1] = 10
    v = vector(v.list() + pad)
    M.append(v)

    for i,v in enumerate(K.basis()):
        v = v[:mc]
        pad = [0] * (d + 1)
        pad[i] = 1

        v = vector(v.list() + pad)
        M.append(v)


    for i in range(d, mc):
        v = [0] * len(M[0])
        v[i] = q
        v = vector(v)
        M.append(v)


    M = Matrix(ZZ, M)
    MLLL = M.BKZ()

    vLLL = MLLL[0]

    if vLLL[-1] < 0:
        vLLL = -vLLL

    ##############

    c1 = copy.copy(c0)
    for i,v in zip(vLLL[-d-1:-1], K.basis()):
        c1 += i * v

    c1 = c1.change_ring(ZZ)
    for i,x in enumerate(c1):
        if x > q/2:
            c1[i] = x - q

    ##############

    m = b - c1 * pk_b
    m = ZZ(m)
    if m > q//2:
        m -= q
    m = ZZ(m % p)

    return m



flag = ""
for A, b in tqdm(zip(encrypt_A, encrypt_b), total=len(encrypt_b)):
    m = solve(A, b)
    print(chr(m))
    flag += chr(m)
    
print(flag)
