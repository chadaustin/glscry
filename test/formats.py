from glscry import *

vertices = Array3f()
colors = Array3f()
normals = Array3f()
texcoords = Array2f()

geo = Geometry()
geo.setVertices(vertices)
testV = ImmediateTest("V", geo)

geo = Geometry()
geo.setVertices(vertices)
geo.setColors(colors)
testVC = ImmediateTest("VC", geo)

geo = Geometry()
geo.setVertices(vertices)
geo.setNormals(normals)
testVN = ImmediateTest("VN", geo)

geo = Geometry()
geo.setVertices(vertices)
geo.setTexCoords(texcoords)
testVT = ImmediateTest("VT", geo)

testList = [testV, testVC, testVN, testVT]

runTests("formats.data", testList, 1, "TriangleRate")
