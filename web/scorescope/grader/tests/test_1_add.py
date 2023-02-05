from util import TestCase

class TestAdd(TestCase):
    def test_add_positive(self):
        self.assertEqual(self.submission.add(1, 2), 3)

    def test_add_negative(self):
        self.assertEqual(self.submission.add(-1, -2), -3)

    def test_add_mixed(self):
        a = [1, -2, 3, 4, -5]
        b = [6, 7, 8, -9, 10]
        c = [7, 5, 11, -5, 5]

        for a, b, c in zip(a, b, c):
            self.assertEqual(self.submission.add(a, b), c)
