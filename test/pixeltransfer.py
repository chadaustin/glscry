from glscry import *

runTests("pixeltransfer.data",
         [CopyPixelTest(), DrawPixelTest(), ReadPixelTest()],
         1,
         "PixelRate")
