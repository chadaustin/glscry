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

type = VertexArrayTest

def buildTextureTest(textureCount):
    geo_vt = Geometry(GL_QUADS)
    geo_vt.vertices  = v

    ts = TextureState()
    for i in range(textureCount):
        texture = Texture()
        texture.minFilter = GL_NEAREST
        texture.magFilter = GL_NEAREST
        ts.setTexture(i, texture)
        geo_vt.texcoords[i] = tc

    stateSet = StateSet()
    stateSet.setState(ts)

    test = type("%d Textures" % textureCount, geo_vt)
    test.addStateSet(stateSet)
    return test

def buildTextureTests():
    t = TextureState()
    return [buildTextureTest(i) for i in range(t.textureCount + 1)]


testList = [type("Flat", geo_v), type("Gouraud", geo_vc)] + \
           buildTextureTests()

runFor = 5 # seconds
results = runTests('Render Mode', testList, runFor)
generateGraph('fillrate', results, 'FillRate')
