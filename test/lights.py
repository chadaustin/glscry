from glscry import *

geo = buildGeometry(GL_TRIANGLES,
        v=defineArray(Array_f, 2, [(0, 0), (0, 1), (1, 1)]),
        n=defineArray(Array_f, 3, [(1, 0, 0), (0, 1, 0), (0, 0, 1)]))

def buildDirectionTest(i):
    state = LightState()
    state.enableLighting = True
    for j in range(len(state.lights)):
        light = state.lights[j]
        light.enable  = j < i
        light.ambient = Vec4f(1, 1, 1, 1)
        light.diffuse = Vec4f(1, 1, 1, 1)
        light.specular = Vec4f(1, 1, 1, 1)
        light.position = Vec4f(0, 0, 1, 0)

    stateSet = StateSet()
    stateSet.setState(state)

    test = VertexArrayTest("%s lights" % i, geo)
    test.addStateSet(stateSet)
    return test

def buildPositionTest(i):
    state = LightState()
    state.enableLighting = True
    for j in range(len(state.lights)):
        light = state.lights[j]
        light.enable  = j < i
        light.ambient = Vec4f(1, 1, 1, 1)
        light.diffuse = Vec4f(1, 1, 1, 1)
        light.specular = Vec4f(1, 1, 1, 1)
        light.position = Vec4f(1, 2, 3, 1)

    stateSet = StateSet()
    stateSet.setState(state)

    test = VertexArrayTest("%s lights" % i, geo)
    test.addStateSet(stateSet)
    return test

def buildSpotTest(i):
    state = LightState()
    state.enableLighting = True
    for j in range(len(state.lights)):
        light = state.lights[j]
        light.enable  = j < i
        light.ambient = Vec4f(1, 1, 1, 1)
        light.diffuse = Vec4f(1, 1, 1, 1)
        light.specular = Vec4f(1, 1, 1, 1)
        light.position = Vec4f(1, 2, 1, 1)
        #light.spotExponent ?
        light.spotCutoff = 45

    stateSet = StateSet()
    stateSet.setState(state)

    test = VertexArrayTest("%s lights" % i, geo)
    test.addStateSet(stateSet)
    return test

def run(filename, testList, type):
    results = runTests(testList, 10)
    generateBarGraph(filename, results, 'VertexRate',
                     xlabel='Number of %s Lights' % type)

lightRange = range(len(LightState().lights) + 1)
run("lights_dir.data",  map(buildDirectionTest, lightRange), 'Directional')
run("lights_pos.data",  map(buildPositionTest,  lightRange), 'Positional')
run("lights_spot.data", map(buildSpotTest,      lightRange), 'Spot')
