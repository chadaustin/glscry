from glscry import *

geo = buildGeometry(GL_TRIANGLES, defineArray(Array_f, 3))

testList = []
for a in ['STREAM_DRAW',
          'STREAM_READ',
          'STREAM_COPY',
          'STATIC_DRAW',
          'STATIC_READ',
          'STATIC_COPY',
          'DYNAMIC_DRAW',
          'DYNAMIC_READ',
          'DYNAMIC_COPY']:

    test = VertexBufferObjectTest(a, geo)
    test.setBufferType(globals()[a])
    testList.append(test)

runTests("vbo.data", testList, 10, "VertexRate")
