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

def run(filename, testtype):
    testList = []
    for i in theRange:
        repeat = range(i)
        
        indices = defineArray(Array_ui, 1, repeat)
    
        geo = buildGeometry(GL_TRIANGLE_STRIP, v=v, i=indices)
        test = testtype(str(i), geo)
        testList.append(test)

    results = runTests(testList, 5)
    generateBarGraph(filename, results, 'VertexRate', xlabel='Indices Used')

run('vertexcache_imm.data', ImmediateTest)
run('vertexcache_dl.data',  DisplayListTest)
run('vertexcache_va.data',  VertexArrayTest)
run('vertexcache_cva.data', CompiledVertexArrayTest)
run('vertexcache_vbo.data', VertexBufferObjectTest)
