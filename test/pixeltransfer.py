from glscry import *

time = 10

copy = CopyPixelTest("Copy")
draw = DrawPixelTest("Draw")
read = ReadPixelTest("Read")
colorResults = runTests([copy, draw, read], time)
colorLine = GraphLine('Color Buffer', colorResults)

copy.copyType = GL_DEPTH
draw.format = GL_DEPTH_COMPONENT
draw.type   = GL_UNSIGNED_INT
read.format = GL_DEPTH_COMPONENT
read.type   = GL_UNSIGNED_INT
depthResults = runTests([copy, draw, read], time)
depthLine = GraphLine('Depth Buffer', depthResults)

generateGraph("pixeltransfer_color", colorLine, "PixelRate")
generateGraph("pixeltransfer_depth", depthLine, "PixelRate")
generateGraph("pixeltransfer", [colorLine, depthLine], "PixelRate")
