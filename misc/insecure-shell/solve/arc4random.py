from Crypto.Cipher import ChaCha20

BUF_SIZE = 1024

class RNG:
    def __init__(self, entropy):
        self.rs_have = 0
        self.rs_count = 0
        self.cipher = None
        self.buf = b''
        self.entropy = entropy

    def rs_init(self, buf):
        if len(buf) < 40:
            return
        key, nonce = buf[:32], buf[32:40]
        self.cipher = ChaCha20.new(key=key, nonce=nonce)

    def rs_stir(self):
        if self.cipher is None:
            self.rs_init(self.entropy)
        else:
            raise NotImplementedError('too much :(')
            # self.rs_rekey(self.entropy())
        self.rs_have = 0
        self.rs_count = 1600000

    def rs_stir_if_needed(self, n):
        if self.rs_count <= n:
            self.rs_stir()
        else:
            self.rs_count -= n

    def rs_rekey(self, dat=None):
        self.buf = self.cipher.encrypt(b'\0'*BUF_SIZE)
        if dat is not None:
            m = min(len(dat, 40))
            for i in range(m):
                self.buf[i] ^= dat[i]
        self.rs_init(self.buf[:40])
        self.rs_have = BUF_SIZE - 40

    def rs_random_buf(self, n):
        rv = b''
        self.rs_stir_if_needed(n)
        while n > 0:
            if self.rs_have > 0:
                m = min(n, self.rs_have)
                rv += self.buf[-self.rs_have:-self.rs_have+m]
                self.rs_have -= m
                n -= m
            if self.rs_have == 0:
                self.rs_rekey()
        return rv

if __name__ == '__main__':
    entropy = bytes.fromhex('98eb82cda9453e4130c00fd9054d1b350d2a0f12772a4784545696cb80dd4fd434e59fb4c2ee89f6')
    r = RNG(entropy)
    r.rs_random_buf(64)
    priv = r.rs_random_buf(32)
    print(priv.hex())
