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

ul = (0, 0)
ll = (0, 1)
lr = (1, 1)
ur = (1, 0)

v = Arrayf(2)
v.repeat = [ul, ll, lr, ur]

c = Arrayf(3)
c.repeat = [r, g, b, w]

n = Arrayf(3)
n.repeat = [r, g, b, w]

tc = Arrayf(2)
tc.repeat = [ul_tc, ll_tc, lr_tc, ur_tc]

geo_v = Geometry(GL_TRIANGLES)
geo_v.vertices = v

geo_vc = Geometry(GL_TRIANGLES)
geo_vc.vertices = v
geo_vc.colors   = c

geo_vt = Geometry(GL_TRIANGLES)
geo_vt.vertices  = v
geo_vt.texcoords = tc

geo_vct = Geometry(GL_TRIANGLES)
geo_vct.vertices  = v
geo_vct.colors    = c
geo_vct.texcoords = tc

type = CompiledVertexArrayTest
t1 = type("V", geo_v)
t2 = type("VC", geo_vc)
t3 = type("VN", geo_vn)
t4 = type("VT", geo_vt)
t5 = type("VCN", geo_vcn)
t6 = type("VCT", geo_vct)
t7 = type("VNT", geo_vnt)
t8 = type("VCNT", geo_vcnt)

runTests('fillrate.py', [t1, t2, t3, t4, t5, t6, t7, t8], 1, "TriangleRate")
