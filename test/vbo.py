from glscry import *

v=defineArray(Array_f, 3)
c=defineArray(Array_f, 3)
n=defineArray(Array_f, 3)
t=defineArray(Array_f, 2)
geo = buildGeometry(GL_TRIANGLES, v=v, c=c, n=n, t=t)

def run(filename, storageMode):
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
        test.setBufferType(globals()['GL_' + a + '_ARB'])
        test.setStorageMode(storageMode)
        testList.append(test)

    runTests(filename, testList, 10, "VertexRate")

SM = VertexBufferObjectTest.StorageMode
run("vbo_separate",    SM.SEPARATE_BUFFERS)
run("vbo_single",      SM.ONE_BUFFER)
run("vbo_interleaved", SM.ONE_BUFFER_INTERLEAVED)
