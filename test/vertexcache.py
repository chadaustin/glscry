from glscry import *
from random import randint

# zeroes should be fine.
v = defineArray(Array_f, 2)
n = defineArray(Array_f, 3, [0, 0, 1])

lightstate = LightState()
for l in lightstate.lights:
    l.enable = True
    l.ambient = Vec4f(0.5, 0.5, 0.5, 1.0)
    l.diffuse = Vec4f(0.5, 0.5, 0.5, 1.0)
    l.specular = Vec4f(0.5, 0.5, 0.5, 1.0)
    
matstate = MaterialState()
matstate.front.shininess = 20
matstate.front.specular = Vec4f(1, 1, 1, 1)
matstate.back = matstate.front

testList = []
for i in [2 ** j for j in range(0, 12)]:
    # hard-coded for default batch size...  bad
    repeat = [randint(0, i-1) for j in range(4096)]
        
    indices = defineArray(Array_ui, 1, repeat)
    
    geo = buildGeometry(GL_TRIANGLE_STRIP, v=v, n=n, i=indices)
    test = VertexArrayTest(str(i), geo)
    test.setState(lightstate)
    test.setState(matstate)
    test.setTransform(
        Vec4f(1, 0, 0, 0),
        Vec4f(0, 1, 0, 0),
        Vec4f(0, 0, 1, 0),
        Vec4f(0, 0, 0, 1))
    testList.append(test)

runTests("vertexcache.data", testList, 10, "VertexRate")
