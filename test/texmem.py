from glscry import *

k = 16 * 2 * 8
runTestsRange("texmem.data", [TextureMemoryTest()], 1.0, "TriangleRate",
              "TextureCount", LinearRange(k, 4096, k))
