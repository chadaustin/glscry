from _glscry import *

def flatten(list):
    r = []
    for a in list:
        if type(a) == type([]) or type(a) == type(()):
            r.extend(flatten(a))
        else:
            r.append(a)
    return r
