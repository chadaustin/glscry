from glscry import *

w = 1024
h = 768

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

tc = Arrayf(2)
tc.repeat = [ul_tc, ll_tc, lr_tc, ur_tc]

geo_v = Geometry(GL_QUADS)
geo_v.vertices = v

geo_vc = Geometry(GL_QUADS)
geo_vc.vertices = v
geo_vc.colors   = c

geo_vt = Geometry(GL_QUADS)
geo_vt.vertices  = v
geo_vt.texcoords = tc

geo_vct = Geometry(GL_QUADS)
geo_vct.vertices  = v
geo_vct.colors    = c
geo_vct.texcoords = tc

type = CompiledVertexArrayTest
test1 = type("Flat", geo_v)
test2 = type("Gouraud", geo_vc)
test3 = type("Tex", geo_vt)
test4 = type("ColoredTex", geo_vct)

runTests('fillrate.py', [test1, test2, test3, test4], 1, "FillRate")
