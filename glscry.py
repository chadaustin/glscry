from _glscry import *

def runTests(filename, testList, runFor, depVar):
    run(lambda: runTests_(filename, testList, runFor, depVar))
