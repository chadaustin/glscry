from glscry import *

def run(fn, begin, end, gen):
    testList = [
        ImmediateTest(gen),
        DisplayListTest(gen),
        VertexArrayTest(gen),
        CompiledVertexArrayTest(gen),
        VertexBufferObjectTest(gen)]

    runTestsRange(fn, testList, 0.2, "TriangleRate",
                  "BatchSize", PowerRange(begin, end))

run("zeroes.data",          1, 18, Zeroes())
run("small_triangles.data", 1, 18, SmallTriangles())
