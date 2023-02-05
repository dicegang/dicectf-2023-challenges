from util import TestCase

class TestLongest(TestCase):
    def test_longest_empty(self):
        self.assertEqual(self.submission.longest([]), None)

    def test_longest_single(self):
        self.assertEqual(self.submission.longest(['a']), 'a')

    def test_longest_multiple(self):
        words = ['a', 'bb', 'ccc', 'dddd', 'eeeee', 'ffffff']
        self.assertEqual(self.submission.longest(words), 'ffffff')

    def test_longest_multiple_tie(self):
        words = ['aaaaaa', 'bb', 'ccc', 'dddd', 'eeeee', 'ffffff']
        self.assertEqual(self.submission.longest(words), 'aaaaaa')
