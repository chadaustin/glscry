from glscry import *

runFor = 5
testType = VertexBufferObjectTest

repeat=[(5, 5, 0, 1), (5, 6, 0, 1), (6, 6, 0, 1)]
v = defineArray(Array_f, 4, repeat)
geo = buildGeometry((GL_TRIANGLES, 20), v=v)

noTransform = testType("None", geo)

identTransform  = testType("Identity", geo)
identTransform.setTransform(IdentityTransform())

def setRow(r, row):
    for i, e in enumerate(row):
        r[i] = e

matrixTransform = testType("Matrix", geo)
mat = Matrix44f()
setRow(mat[0], [1, 0, 0, 0])
setRow(mat[1], [0, 1, 0, 0])
setRow(mat[2], [0, 0, 1, 0])
setRow(mat[3], [0, 0, 0, 1])
matrixTransform.setTransform(MatrixTransform(mat))

testList = [noTransform, identTransform, matrixTransform]

results = runTests('Transform', testList, runFor)
generateGraph('transform', results, "VertexRate", xlabel="Transform Method")
