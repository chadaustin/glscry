from glscry import *

geo = buildGeometry(GL_TRIANGLES,
        v=defineArray(Array_f, 2, [(0, 0), (0, 1), (1, 1)]),
        n=defineArray(Array_f, 3, [(1, 0, 0), (0, 1, 0), (0, 0, 1)]))

def buildDirectionTest(i):
    state = LightState()
    for j in range(len(state.lights)):
        light = state.lights[j]
        light.enable  = j < i
        light.ambient = Vec4f(1, 1, 1, 1)
        light.diffuse = Vec4f(1, 1, 1, 1)
        light.specular = Vec4f(1, 1, 1, 1)
        light.position = Vec4f(0, 0, 1, 0)

    test = VertexArrayTest("%s lights" % i, geo)
    test.setState(state)
    return test

def buildPositionTest(i):
    state = LightState()
    for j in range(len(state.lights)):
        light = state.lights[j]
        light.enable  = j < i
        light.ambient = Vec4f(1, 1, 1, 1)
        light.diffuse = Vec4f(1, 1, 1, 1)
        light.specular = Vec4f(1, 1, 1, 1)
        light.position = Vec4f(1, 2, 3, 1)

    test = VertexArrayTest("%s lights" % i, geo)
    test.setState(state)
    return test

def buildSpotTest(i):
    state = LightState()
    for j in range(len(state.lights)):
        light = state.lights[j]
        light.enable  = j < i
        light.ambient = Vec4f(1, 1, 1, 1)
        light.diffuse = Vec4f(1, 1, 1, 1)
        light.specular = Vec4f(1, 1, 1, 1)
        light.position = Vec4f(1, 2, 1, 1)
        #light.spotExponent ?
        light.spotCutoff = 45;

    test = VertexArrayTest("%s lights" % i, geo)
    test.setState(state)
    return test

lightRange = range(len(LightState().lights) + 1)
runTests("lights_dir.data",  [buildDirectionTest(i) for i in lightRange], 10, "VertexRate")
runTests("lights_pos.data",  [buildPositionTest(i)  for i in lightRange], 10, "VertexRate")
runTests("lights_spot.data", [buildSpotTest(i)      for i in lightRange], 10, "VertexRate")
