from glscry import *

runTestsRange("texmem.data", [TextureMemoryTest("")], 10, "VertexRate",
              "TextureCount", LinearRange(16, 512, 16))
