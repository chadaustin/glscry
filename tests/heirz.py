from glscry import *

genFrontToBack = Geometry()
genBackToFront = Geometry()

frontToBack = VertexArrayTest(genFrontToBack)
backToFront = VertexArrayTest(genBackToFront)

runTests("heir_z.data", [frontToBack, backToFront], 1, "TriangleRate")
