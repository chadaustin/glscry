from glscry import *

copy = CopyPixelTest("Copy")
draw = DrawPixelTest("Draw")
read = ReadPixelTest("Read")
testList = [copy, draw, read]

results = runTests(testList, 5)
generateBarGraph("pixeltransfer.data", testList, results, "PixelRate",
                 'Color Buffer Operation')
