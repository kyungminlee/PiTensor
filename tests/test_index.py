import unittest
import pitensor
import math

class PiTensorTest_Index(unittest.TestCase):
    def test(self):
        self.testIndex()
        self.testIQIndex()

    def testIndex(self):
        i = pitensor.Index("I", 3)
        s = str(i)
        self.assertTrue(s.startswith('(I,3'))

    def testIQIndex(self):
        pass

if __name__=='__main__':
    unittest.main()
