from glscry import *

time = 10

copy = CopyPixelTest("Copy")
draw = DrawPixelTest("Draw")
read = ReadPixelTest("Read")
colorLine = runTests('Color Buffer', [copy, draw, read], time)

copy.copyType = GL_DEPTH
draw.format = GL_DEPTH_COMPONENT
draw.type   = GL_UNSIGNED_INT
read.format = GL_DEPTH_COMPONENT
read.type   = GL_UNSIGNED_INT
depthLine = runTests('Depth Buffer', [copy, draw, read], time)

generateGraph("pixeltransfer_color", colorLine, "PixelRate")
generateGraph("pixeltransfer_depth", depthLine, "PixelRate")
generateGraph("pixeltransfer", [colorLine, depthLine], "PixelRate")
