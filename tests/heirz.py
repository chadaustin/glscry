from glscry import *

genFrontToBack = Zeroes()
genBackToFront = Zeroes()

frontToBack = VertexArrayTest(genFrontToBack)
backToFront = VertexArrayTest(genBackToFront)

runTests("heir_z.data", [frontToBack, backToFront], 1, "TriangleRate")
