from glscry import *

w = 1024
h = 768
o = 1 # offset

ul = (o,     o,     0)
ur = (w-o-o, o,     0)
lr = (w-o-o, h-o-o, 0)
ll = (o,     h-o-o, 0)
quad = [ul, ur, lr, ll]

genFrontToBack = buildGeometry(
    (GL_QUADS, 1024),
    v=defineArray(Array_f, 3, quad, (0, 0, -1) * 4))

genBackToFront = buildGeometry(
    (GL_QUADS, 1024),
    v=defineArray(Array_f, 3, quad, (0, 0, 1) * 4))

depthState = DepthState()
depthState.enableDepthTest = True
colorBufferState = ColorBufferState()
colorBufferState.setWriteMask(False, False, False, False)

stateSet = StateSet()
stateSet.setState(depthState)
stateSet.setState(colorBufferState)

clearAction = ClearAction(GL_DEPTH_BUFFER_BIT)

test1 = ImmediateTest('Front to Back', genFrontToBack)
test1.addStateSet(stateSet)
test1.addAction(clearAction)

test2 = ImmediateTest('Back to Front', genBackToFront)
test2.addStateSet(stateSet)
test2.addAction(clearAction)

results = runTests('Render Order', [test1, test2], 1)
generateGraph("hierz", results, "VertexRate")
