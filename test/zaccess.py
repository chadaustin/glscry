from glscry import *

copy = CopyPixelTest("Copy")
copy.copyType = GL_DEPTH

draw = DrawPixelTest("Draw")
draw.format = GL_DEPTH_COMPONENT
draw.type   = GL_FLOAT

read = ReadPixelTest("Read")
read.format = GL_DEPTH_COMPONENT
read.type   = GL_FLOAT

runTests("zaccess.data", [copy, draw, read], 5, "PixelRate")
