from glscry import *

geo = Geometry(GL_TRIANGLES)
geo.vertices = defineArray(2, [(0, 0), (0, 1), (1, 1)])
geo.normals  = defineArray(3, [(1, 0, 0), (0, 1, 0), (0, 0, 1)])

tests = []

for i in range(8):
    state = LightState()
    for j in range(i):
        state.useLight(j, True)
        state.setAmbient(j, Vec4f(0.5, 0.5, 0.5, 1.0))

    test = VertexArrayTest("%s lights" % i, geo)
    test.setState(state)
    tests.append(test)

runTests("light.data", tests, 10, "VertexRate")
