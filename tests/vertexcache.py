from glscry import *

list = [ IndexedGeometryTest(Zeroes()) ]
runTestsRange("vcache.data", list, 1, "TriangleRate",
              "BatchSize", PowerRange(1, 16))
