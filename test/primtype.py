from glscry import *

w = 1
h = 1

ul = (0, 0)
ll = (0, h)
lr = (w, h)
ur = (w, 0)

def defineGeometry(type, v):
    g = Geometry(type)
    g.vertices = v
    return g

test = CompiledVertexArrayTest
tests = [
    test("POINTS",         defineGeometry(GL_POINTS,         defineArray(Array_f, 2, [ul]))),
    test("LINES",          defineGeometry(GL_LINES,          defineArray(Array_f, 2, [ul, lr]))),
    test("LINE_STRIP",     defineGeometry(GL_LINE_STRIP,     defineArray(Array_f, 2, [ul, lr]))),
    test("LINE_LOOP",      defineGeometry(GL_LINE_LOOP,      defineArray(Array_f, 2, [ul, lr]))),
    test("TRIANGLES",      defineGeometry(GL_TRIANGLES,      defineArray(Array_f, 2, [ul, ll, ur]))),
    test("TRIANGLE_STRIP", defineGeometry(GL_TRIANGLE_STRIP, defineArray(Array_f, 2, [ul, ll, ur]))),
    test("TRIANGLE_FAN",   defineGeometry(GL_TRIANGLE_FAN,   defineArray(Array_f, 2, [ll, ur], initial=[ul]))),
    test("QUADS",          defineGeometry(GL_QUADS,          defineArray(Array_f, 2, [ul, ll, lr, ur]))),
    test("QUAD_STRIP",     defineGeometry(GL_QUAD_STRIP,     defineArray(Array_f, 2, [ul, ll, ur, lr]))),
    test("POLYGON",        defineGeometry(GL_POLYGON,        defineArray(Array_f, 2, [ll, ur], initial=[ul])))]

runTests('primtype.data', tests, 10, "VertexRate")
