from glscry import *
from random import randint

v = defineArray(
    Array_f, 3,
    repeat=[0, 0, 0, 0, 1, 0, 1, 1, 0],
    offset=[0, 0, 1, 0, 0, 1, 0, 0, 1])
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

vertexArraySize = 16384

testList = []
step = 1
for i in range(step, 32, step):#[2 ** j for j in range(0, 12)]:
    repeat = [randint(0, i-1) for j in range(vertexArraySize)]
    # Guarantee that we're using arrays of the same size.
    repeat.append(vertexArraySize)
        
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

runTests("vertexcache.data", testList, 5, "VertexRate")
