import unittest
import pitensor
import math

class PiTensorTest_ITensor(unittest.TestCase):
    def test(self):
        self.testITensor()

    def testITensor(self):
        i = pitensor.Index("I", 3)
        j = pitensor.Index("J", 4)
        T = pitensor.ITensor(i,j)
        T.fill(1.0)
        U = pitensor.ITensor(i)
        S = pitensor.ITensor()
        V = pitensor.ITensor()
        foo = pitensor.svd(T, U, S, V)

        self.assertTrue(math.isclose(pitensor.norm(T), math.sqrt(12.0), rel_tol=1E-6))
        self.assertTrue(math.isclose(pitensor.norm(S), math.sqrt(12.0), rel_tol=1E-6))


        j2 = pitensor.findindex(T, lambda x: x.name == 'J')
        self.assertEqual(j, j2)
        

if __name__=='__main__':
    unittest.main()
