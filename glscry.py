from _glscry import *

def flatten(list):
    r = []
    for a in list:
        if type(a) == type([]) or type(a) == type(()):
            r.extend(flatten(a))
        else:
            r.append(a)
    return r

def runTests(filename, testList, runFor, depVar):
    run(lambda: runTests_(filename, testList, runFor, depVar))

def runTestsRange(filename, testList, runFor, depVar, indVar, range):
    run(lambda: runTestsRange_(filename, testList, runFor, depVar,
                               indVar, range))
