from glscry import *

geo = Zeroes()
testList = [
    ImmediateTest('Immediate', geo),
    DisplayListTest('Display Lists', geo),
    VertexArrayTest('Vertex Arrays', geo),
    CompiledVertexArrayTest('Compiled Vertex Arrays', geo),
    VertexBufferObjectTest('Vertex Buffer Objects', geo)]

results = runTestsRange(testList, 1, 'batchSize', PowerRange(1, 18))
generateGraph('batchsizes_vertexrate', results, 'VertexRate',
              xlabel='Batch Size', graphType=GraphType.LINE)
generateGraph('batchsizes_batchrate', results, 'BatchRate',
              xlabel='Batch Size', graphType=GraphType.LINE)
