from glscry import *

w = 1024
h = 768
o = 1 # offset

ul = (o,     o,     0)
ur = (w-o-o, o,     0)
lr = (w-o-o, h-o-o, 0)
ll = (o,     h-o-o, 0)
quad = [ul, ur, lr, ll]

genFrontToBack = Geometry(GL_QUADS)
genFrontToBack.vertices = defineArray(Array_f, 3, quad, (0, 0, -1))

genBackToFront = Geometry(GL_QUADS)
genBackToFront.vertices = defineArray(Array_f, 3, quad, (0, 0, 1))

depthState = DepthState()
depthState.depthTest = True
colorBufferState = ColorBufferState()
colorBufferState.setWriteMask(False, False, False, False)

test1 = ImmediateTest("FrontToBack", genFrontToBack)
test1.setState(depthState)
test1.setState(colorBufferState)
test1.addAction(ClearAction())

test2 = ImmediateTest("BackToFront", genBackToFront)
test2.setState(depthState)
test2.setState(colorBufferState)
test2.addAction(ClearAction())

runTests("hierz.data", [test1, test2], 10, "VertexRate")
