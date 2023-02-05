from util import TestCase

class TestFavorite(TestCase):
    def test_favorite(self):
        self.assertEqual(self.submission.favorite(), 12)
