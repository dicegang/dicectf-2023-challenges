from util import TestCase

import hashlib

class TestPreimage(TestCase):
    def test_preimage_a(self):
        data = b'dicectf'
        hash = hashlib.sha256(data).hexdigest()
        self.assertEqual(self.submission.preimage(hash), data)

    def test_preimage_b(self):
        target = (
            'b461ed203917d3710f6103c0e77136dd'
            'f1de7e3771eb995d0e913f3677daa490'
        )
        result = self.submission.preimage(target)
        hashed = hashlib.sha256(result).hexdigest()
        self.assertEqual(target, hashed)
