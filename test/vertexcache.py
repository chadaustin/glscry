from glscry import *

list = [ IndexedGeometryTest("Test", Zeroes()) ]
runTestsRange("vcache.data", list, 10, "VertexRate",
              "BatchSize", PowerRange(1, 16))
