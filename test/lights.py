from glscry import *

vertices = Arrayf(2)
vertices.repeat[:] = flatten( [(0, 0), (0, 1), (1, 1)] )

geo = Geometry(GL_TRIANGLES)
geo.vertices = vertices
    

tests = []

for i in range(8):
    state = LightState()
    for j in range(i):
        state.useLight(j, True)
        state.setAmbient(j, Vec4f(0.5, 0.5, 0.5, 1.0))

    test = VertexArrayTest("VertexArray", geo)
    test.setState(state)
    tests.append(test)

runTests("light.data", tests, 1, "TriangleRate")
