# [Begin Copyright Header]
# 
# GLScry - OpenGL Performance Analysis Tool
# Copyright (C) 2004-2005  Iowa State University
# 
# This software is licensed under the terms of the GNU Lesser Public
# License, version 2.1, as published by the Free Software Foundation.  
# See the file COPYRIGHT.txt for details.
# 
# Authors:
#   Chad Austin <aegisk@iastate.edu>
#   Dirk Reiners <dreiners@iastate.edu>
# 
# [End Copyright Header]
import platform
import socket
from _glscry import *


def flatten(list):
    r = []
    for a in list:
        if type(a) == type([]) or type(a) == type(()):
            r.extend(flatten(a))
        else:
            r.append(a)
    return r


def defineArray(arraytype, size, repeat=[], offset=[], initial=[]):
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


def getTitle():
    return '  ::  '.join([
        'GLScry %s' % getVersion(),
        socket.gethostname(),
        glGetString(GL_VENDOR),
        glGetString(GL_RENDERER),
        glGetString(GL_VERSION)])


def writeID(file):
    class Property:
        def __init__(self, name, value):
            self.name  = name
            self.value = value
    propertyList = [
        Property('GLScry Version',  getVersion()),
        Property('Host',            socket.gethostname()),
        Property('Platform',        platform.platform()),
        Property('OpenGL Vendor',   glGetString(GL_VENDOR)),
        Property('OpenGL Renderer', glGetString(GL_RENDERER)),
        Property('OpenGL Version',  glGetString(GL_VERSION)) ]

    processors = getProcessors()
    if len(processors) == 1:
        proc = processors[0]
        propertyList += [
            Property('CPU Type', proc.type),
            Property('CPU Speed', proc.speed) ]
    else:
        for i, proc in enumerate(processors):
            propertyList += [
                Property('CPU%s Type' % i, proc.type),
                Property('CPU%s Speed' % i, proc.speed) ]

    propertyList.append(
        Property('RAM Size', getMemorySize()))

    maxNameLength = max([len(prop.name) for prop in propertyList])
    for prop in propertyList:
        file.write('# %s = %s\n' % (
            prop.name.ljust(maxNameLength),
            prop.value))


class LinearRange:
    def __init__(self, begin, end, step = 1):
        assert step > 0

        self.begin = begin
        self.end   = end
        self.step  = step

    def __iter__(self):
        class Iterable:
            def __init__(self2):
                self2.current = self.begin

            def next(self2):
                if self2.current > self.end:
                    raise StopIteration
                else:
                    value = self2.current
                    self2.current += self.step
                    return value
        return Iterable()


class PowerRange:
    def __init__(self, begin, end, power = 2):
        self.begin = begin
        self.end   = end
        self.power = power

    def __iter__(self):
        class Iterable:
            def __init__(self2):
                self2.current = self.begin

            def next(self2):
                if self2.current > self.end:
                    raise StopIteration
                else:
                    value = self.power ** self2.current
                    self2.current += 1
                    return value
        return Iterable()


def make_unique(list):
    if not list:
        return list

    rv = []

    list.sort()
    last = list[0]
    rv.append(last)
    for b in list[1:]:
        if b != last:
            last = b
            rv.append(last)

    return rv


def uniquePowerRange(low, high, power):
    list = [int(power ** k) for k in range(int(low), int(high + 1))]
    return make_unique(list)


class Result:
    """The result of running a test.

    Result objects are the result of running a test.  They contain three
    fields:

    name         Name of the test.
    resultDescs  List of ResultDesc objects.
    resultSet    ResultSet object (list of numbers).  For any i, the value
                 in result[i] corresponds to resultDescs[i].
    """
    
    def __init__(self, name, resultDescs, resultSet):
        self.name        = name
        self.resultDescs = resultDescs
        self.resultSet   = resultSet


class GraphLine:
    """The result of running a related list of tests."""
    
    def __init__(self, title, resultList):
        self.title = title
        self.resultList = resultList


def runTest(test, runFor, resultName=None, printedName=None):
    """Runs a test and returns a Result object."""
    
    betweenTests()
    
    if not resultName:
        resultName = test.name

    if not printedName:
        printedName = test.name

    try:
        if test.isSupported():
            print "\nRunning test '%s'" % printedName

            resultSet = test.run(runFor)

            for r, d in zip(resultSet, test.getResultDescs()):
                print "  %s = %s %s" % (d.name, r, d.units)

            return Result(resultName, test.getResultDescs(), resultSet)
            
    except GLError, e:
        print e.value()

    # Return zeroes if the test isn't supported or throws an exception.
    resultSet = ResultSet()
    resultSet[:] = [0] * len(test.getResultDescs())
    return Result(resultName, test.getResultDescs(), resultSet)


def runTests(testList, runFor):
    """Runs a list of tests and returns a list of Result objects.

    Returns a list of Result objects containing the results of running
    every test in testList.
    """
    return [runTest(t, runFor) for t in testList]


def runTestRange(test, runFor, variedProperty, range, coerce=None):
    """Runs a test and returns a GraphLine object."""

    resultList = []
    for v in range:
        if coerce:
            v = coerce(v)
        setattr(test, variedProperty, v)
        resultList.append(
            runTest(test,
                    runFor,
                    str(v),
                    '%s (%s = %s)' % (test.name, variedProperty, v)))
    return GraphLine(test.name, resultList)


def runTestsRange(testList, runFor, variedProperty, range, coerce=None):
    """Runs a list of tests and returns a list of GraphLine objects."""
    return [runTestRange(t, runFor, variedProperty, range, coerce) for t in testList]


def reduceResults(resultList, measuredResult):
    """Reduces results returned by runTests to a single list of
    numbers and a units string.

    Given a results list returned by runTests, reduceResults removes
    everything except the results named by the measuredResult parameter.
    If any of the result sets do not contain any results named the
    value of measured, an exception is raised.  Returns a 2-tuple
    where the first element is the list of result values and the
    second is a units string.
    """

    resultDesc = None

    rv = []
    for result in resultList:
        results = result.resultSet
        resultDescs = result.resultDescs
        assert len(resultDescs) == len(results)
        
        resultIndex = -1
        for i in range(len(resultDescs)):
            d = resultDescs[i]
            if d.name == measuredResult:
                resultIndex = i
                if resultDesc is not None:
                    assert d == resultDesc
                else:
                    resultDesc = d
                break
            
        if resultIndex == -1:
            raise IndexError, "Test has no result '%s'" % measuredResult
        
        rv.append(results[resultIndex])
        
    return (rv, resultDesc)


def assertEqual(list):
    if len(list) > 0:
        for v in list[1:]:
            assert list[0] == v


class GraphType:
    class BAR:  typeString = 'boxes'
    class LINE: typeString = 'lines'


def addIf(list, value):
    if value:
        return list[:] + [value]
    else:
        return list


def generateGraph(filename, graphLineList, measured,
                  xlabel=None, graphType=GraphType.BAR, normalizeBy=None):
    
    if type(graphLineList) != type([]):
        graphLineList = [graphLineList]
    
    # Empty lists aren't allowed.
    assert len(graphLineList) >= 1
    assert len(graphLineList[0].resultList) >= 1
    lineCount = len(graphLineList)
    resultCount = len(graphLineList[0].resultList)

    # All of the resultLists must have equal length.
    assertEqual([len(x.resultList) for x in addIf(graphLineList, normalizeBy)])

    # All rows must have equal test names.
    for i in range(resultCount):
        assertEqual([x.resultList[i].name for x in
                     addIf(graphLineList, normalizeBy)])

    # Reduce the graphLineList to a matrix of numbers and a unit.
    reduced = [reduceResults(x.resultList, measured) for x in graphLineList]
    resultMatrix = [x[0] for x in reduced]

    # All result descriptions must be equal.
    assertEqual([x[1] for x in reduced]) 
    resultUnits = reduced[0][1].units

    if normalizeBy:
        normalizeTitle = normalizeBy.title
        normalizeBy = reduceResults(normalizeBy.resultList, measured)
        assert normalizeBy[1] == reduced[0][1]
        normalizeBy = normalizeBy[0]

    # Write the result matrix to a file.
    datafile = filename + '.data'
    print "\nWriting data file: %s" % datafile

    of = open(datafile, 'w')
    writeID(of)

    if normalizeBy:
        for i in range(resultCount):
            for j in range(lineCount):
                print >> of, resultMatrix[j][i] / normalizeBy[i],
            print >> of
    else:
        for i in range(resultCount):
            for j in range(lineCount):
                print >> of, resultMatrix[j][i],
            print >> of

    script = filename + '.gnuplot'
    print "Generating graph script: %s" % script
    plot = open(script, 'w')

    print >> plot, 'set terminal png'
    print >> plot, 'set size 2,2'
    print >> plot, 'set output "%s.png"' % filename
    print >> plot, 'set title "%s"' % getTitle()
    print >> plot, 'set xrange [-0.5:%s]' % (resultCount - 0.5)
    print >> plot, 'set yrange [0:*]'
    if xlabel:
        print >> plot, 'set xlabel "%s"' % xlabel
    if normalizeBy:
        print >> plot, 'set ylabel "Normalized to %s"' % normalizeTitle
    else:
        print >> plot, 'set ylabel "%s"' % resultUnits

    xtics = ', '.join(['"%s" %s' % (graphLineList[0].resultList[i].name, i)
                       for i in range(resultCount)])
    print >> plot, 'set xtics (%s)' % xtics

    plotList = ['"%s" using 0:%s title "%s" with %s' % (datafile, i + 1,
                                                        graphLineList[i].title,
                                                        graphType.typeString)
                for i in range(lineCount)]
    plotStr = ', '.join(plotList)
    print >> plot, 'plot %s' % plotStr
