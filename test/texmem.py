from glscry import *
from math import *

power = 1.2
start = floor(log(8) / log(power))
end   = ceil(log(1024) / log(power))
range = PowerRange(start, end, power)

runTestsRange("texmem.data", [TextureMemoryTest("TextureMemory")], 10,
              "VertexRate", "TextureCount", range)
