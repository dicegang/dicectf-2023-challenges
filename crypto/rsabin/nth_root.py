from sage.all import *

# https://rosettacode.org/wiki/Chinese_remainder_theorem#Python
# lol
from functools import reduce
def chinese_remainder(a, n):
    sum = 0
    prod = reduce(lambda a, b: a*b, n)
    for n_i, a_i in zip(n, a):
        p = prod // n_i
        sum += a_i * mul_inv(p, n_i) * p
    return sum % prod

def mul_inv(a, b):
    b0 = b
    x0, x1 = 0, 1
    if b == 1: return 1
    while a > 1:
        q = a // b
        a, b = b, a%b
        x0, x1 = x1 - q * x0, x0
    if x1 < 0: x1 += b0
    return x1

def get_probable_multiplicative_generator(K):
    phi = K.order() - 1
    prime_base = [p for p in primes_first_n(10000) if gcd(p, phi) > 1]
    for i in range(100):
        g = K.random_element()
        skip = False
        for p in prime_base:
            if g**(phi // p) == 1:
                skip = True
                break
        if skip:
            continue
        return g
    raise ValueError("No suitable generator found")

# https://github.com/sagemath/sage/blob/develop/src/sage/rings/finite_rings/element_base.pyx#L42
def nth_root(h, q, e, all=False, algorithm=None, cunningham=False):
    """
    This function exists to reduce code duplication between finite field
    nth roots and integer_mod nth roots.
    The inputs are described there.
    TESTS::
        sage: a = Zmod(17)(13)
        sage: a._nth_root_common(4, True, "Johnston", False)
        [3, 5, 14, 12]
        sage: a._nth_root_common(4, True, "Johnston", cunningham=True)  # optional - cunningham_tables
        [3, 5, 14, 12]
    """

    self = GF(q)(h)
    n = Integer(e)

    K = self.parent()
    q = K.order()
    if self.is_one():
        gcd = n.gcd(q-1)
        if gcd == 1:
            if all: return [self]
            else: return self
        else:
            g = get_probable_multiplicative_generator(K)
            q1overn = (q-1)//gcd
            nthroot = g**q1overn
            return [nthroot**a for a in range(gcd)] if all else nthroot
    n = n % (q-1)
    if n == 0:
        if all: return []
        else: raise ValueError("no nth root")
    gcd, alpha, beta = n.xgcd(q-1) # gcd = alpha*n + beta*(q-1), so 1/n = alpha/gcd (mod q-1)
    if gcd == 1:
        return [self**alpha] if all else self**alpha
    n = gcd
    q1overn = (q-1)//n
    if self**q1overn != 1:
        if all: return []
        else: raise ValueError("no nth root")
    self = self**alpha
    if cunningham:
        from sage.rings.factorint import factor_cunningham
        F = factor_cunningham(n)
    else:
        F = n.factor()
    from sage.groups.generic import discrete_log
    if algorithm is None or algorithm == 'Johnston':
        g = get_probable_multiplicative_generator(K)
        for r, v in F:
            k, h = (q-1).val_unit(r)
            z = h * (-h).inverse_mod(r**v)
            x = (1 + z) // r**v
            if k == 1:
                self = self**x
            else:
                t = discrete_log(self**h, g**(r**v*h), r**(k-v), operation='*')
                self = self**x * g**(-z*t)
        if all:
            nthroot = g**q1overn
            L = [self]
            for i in range(1,n):
                self *= nthroot
                L.append(self)
            return L
        else:
            return self
    else:
        raise ValueError("unknown algorithm")


if __name__ == "__main__":
    e = 17
    g = 0x1337
    q = 12714807009845447513288106786801833819965238412391646152464915067719025253374740587418172935324874246732231958263491062899331863477609690260932323000702303
    assert (q - 1) % e == 0
    h = pow(g, q, e)

    for i in range(100):
        x = nth_root(h, q, e, True)
        assert 0x1337 in x
