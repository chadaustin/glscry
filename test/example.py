from glscry import *

runFor = 0.1 # seconds

repeat_v = (5, 5, 0) + (5, 6, 0) + (6, 6, 0)
repeat_n = (1, 0, 0) + (0, 1, 0) + (0, 0, 1)
v = defineArray(Array_f, 3, repeat_v)
n = defineArray(Array_f, 3, repeat_n)

geometry = buildGeometry(GL_TRIANGLES, v=v, n=n)

test1 = ImmediateTest("Immediate",     geometry)
test2 = VertexArrayTest("VertexArray", geometry)

testList = [test1, test2]

exampleResultList = runTests('Example Graph Line', testList, runFor)
generateGraph("example", exampleResultList, "VertexRate", xunits='X Units')
