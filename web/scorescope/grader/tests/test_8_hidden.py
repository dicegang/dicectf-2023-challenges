import util

class TestHidden(util.TestCase):
    @util.hidden
    def test_hidden(self):
        raise Exception('failed!')
