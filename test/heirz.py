from glscry import *

w = 1024
h = 768

ul = (0, 0, 0)
ur = (w, 0, 0)
lr = (w, h, 0)
ll = (0, h, 0)
quad = [ul, ur, lr, ll]

def defineArray(repeat, offset):
    array = Arrayf(3)
    array.repeat = repeat
    array.offset = offset
    return array

genFrontToBack = Geometry(GL_QUADS)
genFrontToBack.vertices = defineArray(quad, (4, (0, 0, 1)))

genBackToFront = Geometry(GL_QUADS)
genBackToFront.vertices = defineArray(quad, (4, (0, 0, -1)))

runTests("heir_z.data",
         [VertexArrayTest(genFrontToBack), VertexArrayTest(genBackToFront)],
         1,
         "TriangleRate")
