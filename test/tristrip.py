from glscry import *

runFor = 4 # seconds

gridSize = 100  # width and height of grid on which geometry is generated.
stripCount = 100
testType = VertexBufferObjectTest

grid = [(i % gridSize, i / gridSize)
        for i in range(gridSize * (gridSize + 1))]

def idx(x, y):
    return y * gridSize + x


def buildDegenerateTest(stripLength):
    indices = []

    for y in xrange(stripCount):
        # Start the strip.
        indices += [idx(0, y), idx(0, y + 1)]
    
        # Feed triangles.
        for t in xrange(stripLength):
            last = idx(t / 2 + 1, y + t % 2)
            indices += [last]

        if y + 1 < stripCount:
            # Use degenerate triangles to restart the list.
            indices += [last, idx(0, y + 1)]
        
    geo_degenerate = buildGeometry(
        (GL_TRIANGLE_STRIP, len(indices) - 2),
        v=defineArray(Array_f, 2, grid),
        i=defineArray(Array_ui, 1, indices))

    return testType(str(stripLength), geo_degenerate)

def buildBatchedTest(stripLength):
    batches = []
    indices = []
    
    for y in xrange(stripCount):
        # Start strip.
        indices += [idx(0, y), idx(0, y + 1)]

        # Feed triangles.
        for t in xrange(stripLength):
            indices += [idx(t / 2 + 1, y + t % 2)]

        batches += [(GL_TRIANGLE_STRIP, stripLength)]

    geo_batched = buildGeometry(
        batches,
        v=defineArray(Array_f, 2, grid),
        i=defineArray(Array_ui, 1, indices))
    return testType(str(stripLength), geo_batched)


samples = xrange(1, gridSize, 3)
degenerateTests = [buildDegenerateTest(stripLength) for stripLength in samples]
batchedTests    = [buildBatchedTest(stripLength)    for stripLength in samples]

degenerateResultList = runTests('Degenerate', degenerateTests, runFor)
batchedResultList    = runTests('Batched',    batchedTests,    runFor)

# Using the test results, generate a gnuplot graph script.
generateGraph('tristrip', [degenerateResultList, batchedResultList],
              'VertexRate', xlabel='Strip Length')
