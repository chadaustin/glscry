from glscry import *

runFor = 2 # seconds

# Specify the geometry we want to render with.  The values below are repeated.
repeat_v = (5, 5, 0) + (5, 6, 0) + (6, 6, 0)
repeat_n = (1, 0, 0) + (0, 1, 0) + (0, 0, 1)
v = defineArray(Array_f, 3, repeat_v)
n = defineArray(Array_f, 3, repeat_n)

geometry = buildGeometry((GL_TRIANGLES, 1024), v=v, n=n)

# Compare the rendering speed of immediate mode vs. vertex arrays.
test1 = ImmediateTest("Immediate",     geometry)
test2 = VertexArrayTest("VertexArray", geometry)

# Run the tests.
testList = [test1, test2]
exampleResultList = runTests('Example Graph Line', testList, runFor)

# Using the test results, generate a gnuplot graph script.
generateGraph("example", exampleResultList, "VertexRate", xlabel='X Units')
