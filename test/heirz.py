from glscry import *

w = 1024
h = 768

ul = (0, 0, 0)
ur = (w, 0, 0)
lr = (w, h, 0)
ll = (0, h, 0)
quad = [ul, ur, lr, ll]

genFrontToBack = Geometry(GL_QUADS)
genFrontToBack.vertices = defineArray(3, quad, 4 * (0, 0, 1))

genBackToFront = Geometry(GL_QUADS)
genBackToFront.vertices = defineArray(3, quad, 4 * (0, 0, -1))

test1 = VertexArrayTest("FrontToBack", genFrontToBack)
test1.setState(DepthState())

test2 = VertexArrayTest("BackToFront", genBackToFront)
test2.setState(DepthState())

runTestsRange("heir_z.data", [test1, test2], 10, "VertexRate",
         "BatchSize", LinearRange(2 ** 12, 2 ** 12))
