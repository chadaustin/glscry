from _glscry import *

def flatten(list):
    r = []
    for a in list:
        if type(a) == type([]) or type(a) == type(()):
            r.extend(flatten(a))
        else:
            r.append(a)
    return r

def defineArray(arraytype, size, repeat, offset=[], initial=[]):
    array = arraytype(size)
    array.repeat[:]  = flatten(repeat)
    array.offset[:]  = flatten(offset)
    array.initial[:] = flatten(initial)
    return array

def buildGeometry(type, v=None, c=None, n=None, t=None, i=None):
    geo = Geometry(type)
    if v: geo.vertices  = v
    if c: geo.colors    = c
    if n: geo.normals   = n
    if t: geo.texcoords = t
    if i: geo.indices   = i
    return geo

def Zeroes():
    return buildGeometry(
        GL_TRIANGLES,
        v=defineArray(2, [(0, 0), (0, 0), (0, 0)]))

def SmallTriangles():
    return buildGeometry(
        GL_TRIANGLES,
        v=defineArray(2, [(0, 0), (0, 1), (1, 1)]))
