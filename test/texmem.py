from glscry import *

k = 16 * 2 * 8
runTestsRange("texmem.data", [TextureMemoryTest("")], 10, "VertexRate",
              "TextureCount", LinearRange(k, 4096, k))
