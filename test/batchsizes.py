from glscry import *

geo = Zeroes()
testList = [
    ImmediateTest('Imm', geo),
    DisplayListTest('DL', geo),
    VertexArrayTest('VA', geo),
    CompiledVertexArrayTest('CVA', geo),
    VertexBufferObjectTest('VBO', geo)]

runTestsRange("batchsizes.data", testList, 1, "VertexRate",
              "BatchSize", PowerRange(1, 18))
