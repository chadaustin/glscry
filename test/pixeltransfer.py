from glscry import *

copy = CopyPixelTest("Copy")
draw = DrawPixelTest("Draw")
read = ReadPixelTest("Read")
colorResults = runTests([copy, draw, read], 5)

copy.copyType = GL_DEPTH
draw.format = GL_DEPTH_COMPONENT
draw.type   = GL_FLOAT
read.format = GL_DEPTH_COMPONENT
read.type   = GL_FLOAT
depthResults = runTests([copy, draw, read], 5)

generateBarGraph("pixeltransfer_color", colorResults, "PixelRate")
generateBarGraph("pixeltransfer_depth", depthResults, "PixelRate")
generateBarGraph("pixeltransfer", colorResults + depthResults, "PixelRate")
