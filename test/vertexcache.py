from glscry import *
from random import randint

# zeroes should be fine.
v = defineArray(Array_f, 2)
n = defineArray(Array_f, 3, [0, 0, 1])

state = LightState()
for j in range(8):
    state.useLight(j, True)
    state.setAmbient(j,  Vec4f(0.5, 0.5, 0.5, 1.0))
    state.setDiffuse(j,  Vec4f(0.5, 0.5, 0.5, 1.0))
    state.setSpecular(j, Vec4f(0.5, 0.5, 0.5, 1.0))

testList = []
for i in [2 ** j for j in range(0, 12)]:
    # hard-coded for default batch size...  bad
    repeat = [randint(0, i-1) for j in range(4096)]
        
    indices = defineArray(Array_ui, 1, repeat)
    
    geo = buildGeometry(GL_TRIANGLES, v=v, n=n, i=indices)
    test = DisplayListTest(str(i), geo)
    test.setState(state)
    testList.append(test)

runTests("vertexcache.data", testList, 10, "VertexRate")
