from glscry import *

geo = buildGeometry(GL_QUADS, defineArray(Array_f, 3))

testList = []
for a in ['GL_STREAM_DRAW_ARB',
          'GL_STREAM_READ_ARB',
          'GL_STREAM_COPY_ARB',
          'GL_STATIC_DRAW_ARB',
          'GL_STATIC_READ_ARB',
          'GL_STATIC_COPY_ARB',
          'GL_DYNAMIC_DRAW_ARB',
          'GL_DYNAMIC_READ_ARB',
          'GL_DYNAMIC_COPY_ARB']:

    test = VertexBufferObjectTest(a, geo)
    test.setBufferType(globals()[a])
    testList.append(test)

runTests("vbo.data", testList, 10, "VertexRate")
