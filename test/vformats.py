from glscry import *

w = 1
h = 1

ul = (5,   5)
ll = (5,   5+h)
lr = (5+w, 5+h)
ur = (5+w, 5)

r = (1, 0, 0)
g = (0,0)
b = (0, 0, 1)
w = (1, 1, 1)

ul_tc = (0, 0)
ll_tc = (0, 1)
lr_tc = (1, 1)
ur_tc = (1, 0)

v = defineArray(Array_f, 2, [ul, ll, lr, ur])
c = defineArray(Array_f, 3, [r, g, b, w])
n = defineArray(Array_f, 3, [r, g, b, w])
t = defineArray(Array_f, 2, [ul_tc, ll_tc, lr_tc, ur_tc])

fmt = GL_TRIANGLES
geo_v    = buildGeometry(fmt, v=v)
geo_vc   = buildGeometry(fmt, v=v, c=c)
geo_vn   = buildGeometry(fmt, v=v, n=n)
geo_vt   = buildGeometry(fmt, v=v, t=t)
geo_vcn  = buildGeometry(fmt, v=v, c=c, n=n)
geo_vct  = buildGeometry(fmt, v=v, c=c, t=t)
geo_vnt  = buildGeometry(fmt, v=v, n=n, t=t)
geo_vcnt = buildGeometry(fmt, v=v, c=c, n=n, t=t)

def run(file, test, name):
    tests = [
        test("V", geo_v),
        test("VC", geo_vc),
        test("VN", geo_vn),
        test("VT", geo_vt),
        test("VCN", geo_vcn),
        test("VCT", geo_vct),
        test("VNT", geo_vnt),
        test("VCNT", geo_vcnt)]

    print "Writing data to %s" % file
    line = runTests(name, tests, 10)
    generateGraph(file + '_vertexrate', line, 'VertexRate')
    generateGraph(file + '_datarate',   line, 'DataRate')
    return line

line1 = run('vformats_imm', ImmediateTest,           'Immediate')
line2 = run('vformats_dl',  DisplayListTest,         'Display Lists')
line3 = run('vformats_va',  VertexArrayTest,         'Vertex Arrays')
line4 = run('vformats_cva', CompiledVertexArrayTest, 'Compiled Vertex Arrays')
line5 = run('vformats_vbo', VertexBufferObjectTest,  'Vertex Buffers')

generateGraph('vformats', [line1, line2, line3, line4, line5], 'VertexRate')
