from glscry import *

v=defineArray(Array_f, 3, (5, 5, 0) + (5, 6, 0) + (6, 6, 0))
c=defineArray(Array_f, 3, (1))
n=defineArray(Array_f, 3, (1, 0 0))
t=defineArray(Array_f, 2)
geo = buildGeometry(GL_TRIANGLES, v=v, c=c, n=n, t=t)

def run(filename, storageMode, name):
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

    line = runTests(name, testList, 10)
    generateGraph(filename, line, "VertexRate", xlabel='Buffer Type')
    return line

SM = VertexBufferObjectTest.StorageMode
line1 = run("vbo_separate",    SM.SEPARATE_BUFFERS,       'Separate Buffers')
line2 = run("vbo_single",      SM.ONE_BUFFER,             'Single Buffer')
line3 = run("vbo_interleaved", SM.ONE_BUFFER_INTERLEAVED, 'Interleaved Buffers')
generateGraph('vbo', [line1, line2, line3], 'VertexRate', xlabel='Buffer Type')
