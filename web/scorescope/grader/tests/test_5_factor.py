from util import TestCase

class TestFactor(TestCase):
    def test_factor_small(self):
        target = 6
        a, b = self.submission.factor(target)
        self.assertGreater(a, 1)
        self.assertGreater(b, 1)
        self.assertIsInstance(a, int)
        self.assertIsInstance(b, int)
        self.assertEqual(a * b, target)

    def test_factor_large(self):
        target = 15
        a, b = self.submission.factor(target)
        self.assertGreater(a, 1)
        self.assertGreater(b, 1)
        self.assertIsInstance(a, int)
        self.assertIsInstance(b, int)
        self.assertEqual(a * b, target)

    def test_factor_bigger(self):
        target = int(
            '104279243114222684858035722682016520998648483729735297039215059' +
            '290247501475923136686992290125599984132395950504368624731674202' +
            '859745110681809427836825405161900645327631536181446228457612003' +
            '208204820966683852762606543215018248244642471718460106228654432' +
            '440021228124538159070136465216453239470675927021807764169'
        )
        a, b = self.submission.factor(target)
        self.assertGreater(a, 1)
        self.assertGreater(b, 1)
        self.assertIsInstance(a, int)
        self.assertIsInstance(b, int)
        self.assertEqual(a * b, target)
