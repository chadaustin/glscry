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

def Zeroes():
    return buildGeometry(
        GL_TRIANGLES,
        v=defineArray(Array_f, 2))

def SmallTriangles():
    return buildGeometry(
        GL_TRIANGLES,
        v=defineArray(Array_f, 2, [(0, 0), (0, 1), (1, 1)]))

def getTitle():
    vendor   = glGetString(GL_VENDOR)
    renderer = glGetString(GL_RENDERER)
    version  = glGetString(GL_VERSION)
    return '(%s), (%s), (%s)' % (vendor, renderer, version)

def writeID(file):
    file.write("# Vendor   = %s\n" % glGetString(GL_VENDOR))
    file.write("# Renderer = %s\n" % glGetString(GL_RENDERER))
    file.write("# Version  = %s\n" % glGetString(GL_VERSION))

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

def runTests(testList, runFor):
    resultList = []
    
    for t in testList:
        betweenTests()

        if t.isSupported():
            print "\nRunning test '%s'" % t.name

            results = t.run(runFor)

            for r, d in zip(results, t.getResultDescs()):
                print "  %s = %s %s" % (d.name, r, d.units)
            
            resultList += [results]
        else:
            results = ResultSet()
            results[:] = [0] * len(t.getResultDescs())
            resultList += [results]

    return resultList

def runTestsRange(filename, testList, runFor, depVar, indVar, range):
    print "\nGenerating data for %s" % filename

    of = open(filename, 'w')
    writeID(of)

    for indValue in range:
        indValue = int(indValue)
        for t in testList:
            betweenTests()

            t.setProperty(indVar, indValue)
            if t.isSupported():
                results = t.run(runFor)
                output(of, t, results, depVar, indVar, indValue)
            else:
                pass # output a zero?
        of.write('\n')

    if testList:
        test = testList[0]
        descs = test.getResultDescs()
        desc = descs[0]

        generateLineGraph(filename, testList,
                          desc.name + " in " + desc.units,
                          indVar, range)

def generateBarGraph(datafile, testList, resultList, measured, xlabel=None):
    print "\nWriting data file: %s" % datafile

    resultUnits = None

    of = open(datafile, 'w')
    writeID(of)
    for t, r in zip(testList, resultList):
        descs = t.getResultDescs()
        assert len(descs) == len(r)

        resultIndex = -1;
        for i in range(len(descs)):
            d = descs[i]
            if d.name == measured:
                resultIndex = i
                if resultUnits:
                    assert d.units == resultUnits
                else:
                    resultUnits = d.units
                break

        if resultIndex == -1:
            raise IndexError, 'Test has no such result'
        result = r[resultIndex]

        print >> of, result

    
    script = datafile + '.sh'
    print "Generating graph script: %s" % script
    plot = open(script, 'w')

    print >> plot, '#!/bin/sh'
    print >> plot, 'cat <<EOF | gnuplot'
    print >> plot, 'set terminal png'
    print >> plot, 'set size 2,2'
    print >> plot, 'set output "%s.png"' % datafile
    print >> plot, 'set title "%s"' % getTitle()
    print >> plot, 'set xrange [-0.5:%s]' % (len(testList) - 0.5)
    print >> plot, 'set yrange [0:*]'
    if xlabel:
        print >> plot, 'set xlabel "%s"' % xlabel
    print >> plot, 'set ylabel "%s"' % resultUnits
    print >> plot, 'set xtics (',
    for i in range(len(testList)):
        t = testList[i]
        print >> plot, '"%s" %s' % (t.name, i),
        if i + 1 < len(testList):
            print >> plot, ', ',
    print >> plot, ')'

    print >> plot, 'plot "%s" using 0:1 with boxes' % datafile
    print >> plot, 'EOF'


def generateLineGraph(datafile, testList, resultUnits, indVar, theRange):
    script = datafile + ".sh"
    print '\nGenerating gnuplot script: ' + script
    plot = open(script, 'w')

    print >> plot, '#!/bin/sh'
    print >> plot, 'cat <<EOF | gnuplot'
    print >> plot, 'set terminal png'
    print >> plot, 'set size 2,2'
    print >> plot, 'set output "%s.png"' % datafile
    print >> plot, 'set title "%s"' % getTitle()
    print >> plot, 'set yrange [0:*]'
    print >> plot, 'set xlabel "%s"' % indVar
    print >> plot, 'set ylabel "%s"' % resultUnits
    print >> plot, 'set xtics (',
    first = True
    j = 0
    for i in theRange:
        if not first:
            print >> plot, ', ',
        first = False
        print >> plot, '"%s" %s' % (i, j),
        j = j + 1
    print >> plot, ')'

    print >> plot, 'plot \\'
    for i in range(len(testList)):
        t = testList[i]
        print >> plot, '  "%s" using 0:%d title "%s" with lines' % (datafile, i + 1, t.getName()),
        if i + 1 < len(testList):
            print >> plot, ',\\',
        print >> plot

    print >> plot, 'EOF'


def output(file, test, results, depVar, indVar = None, indValue = None):
    descs = test.getResultDescs()
    assert len(descs) == len(results)

    resultIndex = -1;
    for i in range(len(descs)):
        d = descs[i]
        if d.name == depVar:
            resultIndex = i
            break

    if resultIndex == -1:
        raise IndexError, 'Test has no such result'
    desc   = descs[resultIndex]
    result = results[resultIndex]

    print >> file, result,

    print '  ' + test.getName(),
    if indVar and indValue:
        print '(%s=%s)' % (indVar, indValue),
    print ': %s = %s %s' % (desc.name, long(result), desc.units)
