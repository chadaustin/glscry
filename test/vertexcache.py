from glscry import *
from random import randint

# zeroes should be fine.
v = defineArray(Array_f, 2)

testList = []
for i in [2 ** j for j in range(0, 12)]:
    repeat = [randint(0, i-1) for j in range(4096)] # hard-coded default batch size...  bad
        
    indices = defineArray(Array_ui, 1, repeat)
    
    geo = buildGeometry(GL_TRIANGLES, v=v, i=indices)
    testList.append(VertexArrayTest(str(i), geo))

runTests("vertexcache.data", testList, 10, "VertexRate")
