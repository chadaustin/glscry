from glscry import *

v = defineArray(Array_f, 3, [(5, 5, 0) + (5, 6, 0) + (6, 6, 0)])
geo = buildGeometry((GL_TRIANGLE_STRIP, 1024), v=v)
testList = [
    ImmediateTest('Immediate', geo),
    DisplayListTest('Display Lists', geo),
    VertexArrayTest('Vertex Arrays', geo),
    CompiledVertexArrayTest('Compiled Vertex Arrays', geo),
    VertexBufferObjectTest('Vertex Buffer Objects', geo)]

def setBatchSize(test, size):
    test.geometry.batches[0].batchSize = size

results = runTestsRange(testList, 1, setBatchSize, PowerRange(1, 18))
generateGraph('batchsizes_vertexrate', results, 'VertexRate',
              xlabel='Batch Size', graphType=GraphType.LINE)
generateGraph('batchsizes_batchrate', results, 'BatchRate',
              xlabel='Batch Size', graphType=GraphType.LINE)
