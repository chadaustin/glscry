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

stateSet = StateSet()
stateSet.setState(depthState)
stateSet.setState(colorBufferState)

clearAction = ClearAction(GL_DEPTH_BUFFER_BIT)

test1 = ImmediateTest("FrontToBack", genFrontToBack)
test1.addStateSet(stateSet)
test1.addAction(clearAction)

test2 = ImmediateTest("BackToFront", genBackToFront)
test2.addStateSet(stateSet)
test2.addAction(clearAction)

runTests("hierz.data", [test1, test2], 10, "VertexRate")
