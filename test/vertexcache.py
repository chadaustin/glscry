from glscry import *
from random import randint
from math import *

v = defineArray(Array_f, 3, [0,0,0])

vertexArraySize = 16384

power = 1.1
start = 1
end   = 1024
theRange = uniquePowerRange(
    floor(log(start) / log(power)),
    ceil(log(end) / log(power)),
    power)

testList = []
for i in theRange:
    repeat = range(i)
        
    indices = defineArray(Array_ui, 1, repeat)
    
    geo = buildGeometry(GL_TRIANGLE_STRIP, v=v, i=indices)
    test = VertexArrayTest(str(i), geo)
    testList.append(test)

runTests("vertexcache.data", testList, 5, "VertexRate")
