from glscry import *

runTests("pixeltransfer.data",
         [CopyPixelTest("Copy"), DrawPixelTest("Draw"), ReadPixelTest("Read")],
         5,
         "PixelRate")
