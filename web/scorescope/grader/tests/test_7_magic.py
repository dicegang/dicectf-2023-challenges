from util import TestCase

import random

class TestMagic(TestCase):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.rng = random.Random()

    def test_magic_a(self):
        self.assertEqual(self.submission.magic(), 31)

    def test_magic_b(self):
        self.assertEqual(self.submission.magic(), self.rng.randint(0, 255))

    def test_magic_c(self):
        targets = [self.rng.randint(0, 255) for _ in range(64)]
        correct = [int(self.submission.magic()) for _ in range(64)]
        wrong = [int(self.submission.magic()) for _ in range(64)]
        self.assertEqual(correct, targets)
        self.assertNotEqual(wrong, targets)
