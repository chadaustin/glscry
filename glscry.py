from _glscry import *

def runTests(filename, testList, runFor, depVar):
    run(lambda: runTests_(filename, testList, runFor, depVar))

def runTestsRange(filename, testList, runFor, depVar, indVar, range):
    run(lambda: runTestsRange_(filename, testList, runFor, depVar,
                               indVar, range))
