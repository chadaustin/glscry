from _glscry import *

def flatten(list):
    r = []
    for a in list:
        if type(a) == type([]) or type(a) == type(()):
            r.extend(flatten(a))
        else:
            r.append(a)
    return r

def defineArray(size, repeat, offset = []):
    array = Arrayf(size)
    array.repeat[:] = flatten(repeat)
    array.offset[:] = flatten(offset)
    return array

def Zeroes():
    geo = Geometry(GL_TRIANGLES)
    geo.vertices = defineArray(2, [(0, 0), (0, 0), (0, 0)])
    return geo

def SmallTriangles():
    geo = Geometry(GL_TRIANGLES)
    geo.vertices = defineArray(2, [(0, 0), (0, 1), (1, 1)])
    return geo
