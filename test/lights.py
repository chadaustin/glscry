from glscry import *

geo = buildGeometry((GL_TRIANGLES, 1024),
        v=defineArray(Array_f, 2, [(5, 5), (5, 6), (6, 6)]),
        n=defineArray(Array_f, 3, [(1, 0, 0), (0, 1, 0), (0, 0, 1)]))

def dirLight(light):
    light.ambient = Vec4f(1, 1, 1, 1)
    light.diffuse = Vec4f(1, 1, 1, 1)
    light.specular = Vec4f(1, 1, 1, 1)
    light.position = Vec4f(0, 0, 1, 0)

def posLight(light):
    light.ambient = Vec4f(1, 1, 1, 1)
    light.diffuse = Vec4f(1, 1, 1, 1)
    light.specular = Vec4f(1, 1, 1, 1)
    light.position = Vec4f(1, 2, 3, 1)

def spotLight(light):
    light.ambient = Vec4f(1, 1, 1, 1)
    light.diffuse = Vec4f(1, 1, 1, 1)
    light.specular = Vec4f(1, 1, 1, 1)
    light.position = Vec4f(1, 2, 1, 1)
    #light.spotExponent ?
    light.spotCutoff = 45

def makeTest(buildLight, i):
    state = LightState()
    state.enableLighting = True
    for j in range(len(state.lights)):
        light = state.lights[j]
        light.enable  = j < i
        buildLight(light)

    test = VertexArrayTest('%s lights' % i, geo)
    test.addStateSet(StateSet(state))
    return test

def run(shortname, testList, type):
    line = runTests(type, testList, 10)
    generateGraph('lights_' + shortname, line, 'VertexRate',
                  xlabel='Number of Lights')
    return line

lights = range(len(LightState().lights) + 1)
lines = [
    run('dir',  [makeTest(dirLight,  i) for i in lights], 'Directional'),
    run('pos',  [makeTest(posLight,  i) for i in lights], 'Positional'),
    run('spot', [makeTest(spotLight, i) for i in lights], 'Spot') ]
generateGraph("lights", lines, 'VertexRate', xlabel='Number of Lights')
