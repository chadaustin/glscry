from glscry import *

w = 1
h = 1

ul = (0, 0)
ll = (0, h)
lr = (w, h)
ur = (w, 0)

r = (1, 0, 0)
g = (0, 1, 0)
b = (0, 0, 1)
w = (1, 1, 1)

ul_tc = (0, 0)
ll_tc = (0, 1)
lr_tc = (1, 1)
ur_tc = (1, 0)

v = defineArray(2, [ul, ll, lr, ur])
c = defineArray(3, [r, g, b, w])
n = defineArray(3, [r, g, b, w])
t = defineArray(2, [ul_tc, ll_tc, lr_tc, ur_tc])

fmt = GL_TRIANGLES
geo_v    = buildGeometry(fmt, v=v)
geo_vc   = buildGeometry(fmt, v=v, c=c)
geo_vn   = buildGeometry(fmt, v=v, n=n)
geo_vt   = buildGeometry(fmt, v=v, t=t)
geo_vcn  = buildGeometry(fmt, v=v, c=c, n=n)
geo_vct  = buildGeometry(fmt, v=v, c=c, t=t)
geo_vnt  = buildGeometry(fmt, v=v, n=n, t=t)
geo_vcnt = buildGeometry(fmt, v=v, c=c, n=n, t=t)

def run(file, test):
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
    runTests(file, tests, 10, "VertexRate")

run('vformats_imm.data', ImmediateTest)
run('vformats_dl.data',  DisplayListTest)
run('vformats_va.data',  VertexArrayTest)
run('vformats_cva.data', CompiledVertexArrayTest)
run('vformats_vbo.data', VertexBufferObjectTest)
