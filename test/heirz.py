from glscry import *

w = 1024
h = 768

ul = (0, 0, 0)
ur = (w, 0, 0)
lr = (w, h, 0)
ll = (0, h, 0)
quad = [ul, ur, lr, ll]

def flatten(list):
    r = []
    for a in list:
        if type(a) == type([]) or type(a) == type(()):
            r.extend(flatten(a))
        else:
            r.append(a)
    return r

def defineArray(repeat, offset):
    array = Arrayf(3)
    array.repeat[:] = flatten(repeat)
    array.offset[:] = flatten(offset)
    return array

genFrontToBack = Geometry(GL_QUADS)
genFrontToBack.vertices = defineArray(quad, 4 * (0, 0, 1))

genBackToFront = Geometry(GL_QUADS)
genBackToFront.vertices = defineArray(quad, 4 * (0, 0, -1))

runTests("heir_z.data",
         [VertexArrayTest("FrontToBack", genFrontToBack),
          VertexArrayTest("BackToFront", genBackToFront)],
         1,
         "VertexRate")
