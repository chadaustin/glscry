from glscry import *

copy = CopyPixelTest("Copy")
draw = DrawPixelTest("Draw")
read = ReadPixelTest("Read")
generateBarGraph(
    "pixeltransfer.data",
    runTests([copy, draw, read], 5),
    "PixelRate",
    'Color Buffer Operation')
