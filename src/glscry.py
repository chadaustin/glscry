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
import pprint
import socket
import time
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


def buildGeometry(typeAndSize, v=None, c=None, n=None, t=None, i=None):
    primtype, batchSize = typeAndSize
    geo = Geometry(primtype, batchSize)
    if i: geo.indices   = i
    if v: geo.vertices  = v
    if c: geo.colors    = c
    if n: geo.normals   = n
    if t:
        if type(t) is not list:
            t = [t]
        geo.texcoords[:] = t
    return geo


def getTitle():
    return '  ::  '.join([
        'GLScry %s' % getVersion(),
        socket.gethostname(),
        glGetString(GL_VENDOR),
        glGetString(GL_RENDERER),
        glGetString(GL_VERSION)])


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


def DisplayListTest(name, geo):
    test = ImmediateTest(name, geo)
    test.useList = True
    return test


def CompiledVertexArrayTest(name, geo):
    test = VertexArrayTest(name, geo)
    test.compiled = True
    return test


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


class Result:
    """\
    A scalar value with an associated name and units.
    """
    def __init__(self, name, value, units):
        self.name  = name
        self.value = value
        self.units = units


class ResultSet:
    """\
    The result of running a single test.

    ResultSet objects contain the results of running a single test.
    Tests can give back multiple results: for example, a geometry test
    might return a vertex rate, primitive rate, data rate, and batch
    rate.  They contain two fields:

    name         Name of the result list.  This is the test name in a bar
                 graph-like test or a value in a test that varies over a
                 range of parameters.  When a point is plotted on a graph,
                 the name corresponds to the x axis.

    results      List of Result objects.
    """

    def __init__(self, name, results):
        assert type(name) is str
        assert type(results) is list

        self.name    = name
        self.results = results


class GraphLine:
    """\
    The result of running a list of tests.  Contains a title and a
    list of ResultSet objects.
    """
    def __init__(self, title, resultSetList):
        assert type(title) is str
        assert type(resultSetList) is list

        self.title = title
        self.resultSetList = resultSetList


def runTest(test, runFor, resultName=None, printedName=None):
    """\
    Runs a test and returns a ResultSet object.
    """

    betweenTests()

    if not resultName:
        resultName = test.name

    if not printedName:
        printedName = test.name

    def makeResultSet(resultSet):
        results = [Result(d.name, value, d.units)
                   for value, d in zip(resultSet, test.getResultDescs())]
        return ResultSet(resultName, results)

    GLError = RuntimeError
    try:
        print "\nRunning test '%s'" % printedName

        if test.isSupported():
            resultSet = test.run(runFor)

            for value, desc in zip(resultSet, test.getResultDescs()):
                print "  %s = %s %s" % (desc.name, value, desc.units)

            return makeResultSet(resultSet)
        else:
            print "  Unsupported"

    except GLError, e:
        print e

    # Return zeroes if the test isn't supported or throws an exception.
    resultSet = ResultValues()
    resultSet[:] = [0] * len(test.getResultDescs())
    return makeResultSet(resultSet)


def runTests(lineTitle, testList, runFor):
    """\
    Runs every test in testList for runFor seconds, then returns a GraphLine
    titled with lineTitle and containing a list of ResultSet objects corresponding
    to each test.
    """
    return GraphLine(lineTitle, [runTest(t, runFor) for t in testList])


def identity(v):
    return v


def runTestRange(test, runFor, variedProperty, range, coerce=identity):
    """\
    Runs a test by varying 'variedProperty' over the range 'range' and
    returns a GraphLine object.
    """

    resultSetList = []
    for v in range:
        v = coerce(v)
        setattr(test, variedProperty, v)
        resultSet = runTest(test, runFor, str(v),
                            '%s (%s = %s)' % (test.name, variedProperty, v))
        resultSetList.append(resultSet)

    return GraphLine(test.name, resultSetList)


def runTestsRange(testList, runFor, variedProperty, range, coerce=identity):
    """\
    Runs a list of tests with runTestsRange and returns a list of
    GraphLine objects.
    """
    return [runTestRange(t, runFor, variedProperty, range, coerce)
            for t in testList]


def assertEqual(list):
    if len(list) > 0:
        for v in list[1:]:
            assert list[0] == v


def reduceResults(resultSetList, measuredResult):
    """\
    Reduces ResultSets returned by runTests to a single list of
    numbers and a units string.

    Given a ResultSets list returned by runTests, reduceResults
    removes everything except the results named by the measuredResult
    parameter.  If any of the result sets do not contain any results
    named the value of measured, an exception is raised.  Returns a
    2-tuple where the first element is the list of result scalars and
    the second is a units string.
    """

    rv = []
    for resultSet in resultSetList:
        result = None
        for r in resultSet.results:
            if r.name == measuredResult:
                result = r
                break

        if result:
            rv.append(result)
        else:
            raise IndexError, "Test has no result '%s'" % measuredResult

    assert len(rv) > 0
    assertEqual([r.name  for r in rv])
    assertEqual([r.units for r in rv])
    return ([r.value for r in rv], rv[0].units)


class GraphType:
    class BAR:  typeString = 'boxes'
    class LINE: typeString = 'lines'


def addIf(list, value):
    if value:
        return list + [value]
    else:
        return list


def div(num, den):
    if den == 0:
        return 0
    else:
        return num / den



def _generateActualGraph(filename, graphLineList, measured,
                         xunits=None, graphType=GraphType.BAR, normalizeBy=None):

    ### Make several checks that the data is combined the right way.

    # Empty lists aren't allowed.
    assert len(graphLineList) >= 1
    assert len(graphLineList[0].resultSetList) >= 1
    lineCount = len(graphLineList)
    resultCount = len(graphLineList[0].resultSetList)

    # All of the resultLists must have equal length.
    assertEqual([len(x.resultSetList) for x in addIf(graphLineList, normalizeBy)])

    # All rows must have equal test names.
    for i in range(resultCount):
        assertEqual([x.resultSetList[i].name for x in
                     addIf(graphLineList, normalizeBy)])

    # Reduce the graphLineList to a matrix of numbers and a unit.
    reduced = [reduceResults(x.resultSetList, measured) for x in graphLineList]
    resultMatrix = [x[0] for x in reduced]

    # All result descriptions must be equal.
    assertEqual([x[1] for x in reduced])
    resultUnits = reduced[0][1]

    if normalizeBy:
        normalizeTitle = normalizeBy.title
        normalizeBy = reduceResults(normalizeBy.resultSetList, measured)
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
                print >> of, div(resultMatrix[j][i], normalizeBy[i]),
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
    if xunits:
        print >> plot, 'set xlabel "%s"' % xunits
    if normalizeBy:
        print >> plot, 'set ylabel "Normalized to %s"' % normalizeTitle
    else:
        print >> plot, 'set ylabel "%s"' % resultUnits

    xtics = ', '.join(['"%s" %s' % (graphLineList[0].resultSetList[i].name, i)
                       for i in range(resultCount)])
    print >> plot, 'set xtics (%s)' % xtics

    plotList = ['"%s" using 0:%s title "%s" with %s' % (datafile, i + 1,
                                                        graphLineList[i].title,
                                                        graphType.typeString)
                for i in range(lineCount)]
    plotStr = ', '.join(plotList)
    print >> plot, 'plot %s' % plotStr


def generateGraph(filename, graphLineList, measured,
                  xlabel=None, graphType=GraphType.BAR, normalizeBy=None):

    ### Make several checks that the data is combined the right way.

    if type(graphLineList) != type([]):
        graphLineList = [graphLineList]


    # Write to JSON file.
    cpuArray = []
    for p in getProcessors():
        cpuArray.append({
            'Type':  p.type,
            'Speed': p.speed})

    systemObj = {}
    systemObj['Host']            = socket.gethostname()
    systemObj['Platform']        = platform.platform()
    systemObj['OpenGL Vendor']   = glGetString(GL_VENDOR)
    systemObj['OpenGL Renderer'] = glGetString(GL_RENDERER)
    systemObj['OpenGL Version']  = glGetString(GL_VERSION)
    systemObj['CPUs']            = cpuArray
    systemObj['RAM Size']        = getMemorySize()

    linesArray = []
    for line in graphLineList:
        data = []
        for resultSet in line.resultSetList:
            results = [{"Name":  result.name,
                        "Value": result.value,
                        "Units": result.units }
                       for result in resultSet.results]

            data.append({ "Name":    resultSet.name,
                          "Results": results })

        linesArray.append({
            'Title': line.title,
            'ResultSet': data})

    testObj = {}
    #testObj['Name'] = testName
    if xlabel:
        testObj['XUnits'] = xlabel
    testObj['GraphLines'] = linesArray

    obj = {}
    obj['GLScry Version'] = getVersion()
    obj['Timestamp']      = time.asctime()
    obj['System']         = systemObj
    obj['Test']           = testObj


    of = open(filename + '.testresult', 'w')
    pprint.pprint(obj, of)

    return _generateActualGraph(filename, graphLineList, measured, xlabel,
                                graphType, normalizeBy)
