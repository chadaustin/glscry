from glscry import *

def run(fn, begin, end, geo):
    testList = [
        ImmediateTest('Imm', geo),
        DisplayListTest('DL', geo),
        VertexArrayTest('VA', geo),
        CompiledVertexArrayTest('CVA', geo),
        VertexBufferObjectTest('VBO', geo)]

    runTestsRange(fn, testList, 1, "VertexRate",
                  "BatchSize", PowerRange(begin, end))

run("zeroes.data",          1, 18, Zeroes())
run("small_triangles.data", 1, 18, SmallTriangles())
