from glscry import *
from math import *

test = TextureMemoryTest("Texture Memory")

power = 1.2
start = floor(log(8) / log(power))
end   = ceil(log(768) / log(power))
range = PowerRange(start, end, power)

results = runTestRange(test, 10, "textureCount", range, int)
generateGraph('texmem', results, 'VertexRate')
