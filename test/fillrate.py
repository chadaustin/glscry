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

ul_tc = (0, 0)
ll_tc = (0, 1)
lr_tc = (1, 1)
ur_tc = (1, 0)

v  = defineArray(Array_f, 2, [ul, ll, lr, ur])
c  = defineArray(Array_f, 3, [r, g, b, w])
tc = defineArray(Array_f, 2, [ul_tc, ll_tc, lr_tc, ur_tc])

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

texState = TextureState()
texState.texture = Texture()
texState.texture.minFilter = GL_NEAREST
texState.texture.magFilter = GL_NEAREST

stateSet = StateSet()
stateSet.setState(texState)

type = ImmediateTest
test1 = type("Flat", geo_v)
test2 = type("Gouraud", geo_vc)
test3 = type("Tex", geo_vt)
test3.addStateSet(stateSet)
test4 = type("ColoredTex", geo_vct)
test4.addStateSet(stateSet)

runTests('fillrate', [test1, test2, test3, test4], 1, "FillRate")
