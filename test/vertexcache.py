from glscry import *
from random import randint
from math import *

v = defineArray(Array_f, 3, [5, 5, 0] + [5, 6, 0] + [6, 6, 0])

vertexArraySize = 16384

power = 1.1
start = 1
end   = 1024
theRange = uniquePowerRange(
    floor(log(start) / log(power)),
    ceil(log(end) / log(power)),
    power)

def run(filename, testtype, name):
    testList = []
    for i in theRange:
        repeat = range(i)
        
        indices = defineArray(Array_ui, 1, repeat)
    
        geo = buildGeometry(GL_TRIANGLE_STRIP, v=v, i=indices)
        test = testtype(str(i), geo)
        testList.append(test)

    results = runTests(testList, 5)
    line = GraphLine(name, results)
    generateGraph(filename, line, 'VertexRate', xlabel='Referenced Indices')
    return line

line1 = run('vertexcache_imm', ImmediateTest,           'Immediate')
line2 = run('vertexcache_dl',  DisplayListTest,         'Display Lists')
line3 = run('vertexcache_va',  VertexArrayTest,         'Vertex Arrays')
line4 = run('vertexcache_cva', CompiledVertexArrayTest, 'Compiled Vertex Arrays')
line5 = run('vertexcache_vbo', VertexBufferObjectTest,  'Vertex Buffer Objects')

generateGraph('vertexcache', [line1, line2, line3, line4, line5], 'VertexRate',
              xlabel='Referenced Indices')
