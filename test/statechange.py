from glscry import *
from math import *

def runStateChange(suffix, state1, state2):
    TestType = VertexArrayTest
    finishAction = FinishAction()

    v = defineArray(Array_f, 2, (5, 5) + (5, 6) + (6, 6))
    geo = buildGeometry(GL_TRIANGLES, v=defineArray(Array_f, 2))
    testNoChange       = TestType("No Change",          geo)
    testChange         = TestType("Change",             geo)
    testNoChangeFull   = TestType("No Change - Full",   geo)
    testChangeFull     = TestType("Change - Full",      geo)
    testNoChangeFinish = TestType("No Change - Finish", geo)
    testChangeFinish   = TestType("Change - Finish",    geo)

    for t in [testNoChange, testNoChangeFull, testNoChangeFinish]:
        t.addStateSet(state1)

    for t in [testChange, testChangeFull, testChangeFinish]:
        t.addStateSet(state1)
        t.addStateSet(state2)

    for t in [testNoChangeFull, testChangeFull]:
        t.fullStateSwitch = True

    for t in [testNoChangeFinish, testChangeFinish]:
        t.addAction(finishAction)

    testList = [
        testNoChange,
        testChange,
        testNoChangeFull,
        testChangeFull]
    #testList.extend([testNoChangeFinish, testChangeFinish])

    power = 1.4
    start = floor(log(1) / log(power))
    end   = ceil(log(4096) / log(power))
    range = uniquePowerRange(start, end, power)

    results = runTestsRange(testList, 1, 'batchSize', range)
    generateGraph('statechange_%s' % suffix, results, "VertexRate",
                  graphType=GraphType.LINE, normalizeBy=results[0])

def buildTextureSS():
    state = TextureState()
    state.texture = Texture()
    return StateSet(state)

def buildDepthSS(func, mask):
    state = DepthState()
    state.enableDepthTest = True
    state.depthFunc = func
    state.depthMask = mask
    return StateSet(state)

def buildBlendSS(enable, src, dst):
    state = BlendState()
    state.enableBlend = enable
    state.srcFactor = src
    state.dstFactor = dst
    return StateSet(state)

def buildLineSS(enableStipple, stippleFactor, stipplePattern):
    state = LineState()
    state.enableStipple = enableStipple
    state.stippleFactor = stippleFactor
    state.stipplePattern = stipplePattern
    return StateSet(state)

runStateChange('blend',
               buildBlendSS(True, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA),
               buildBlendSS(False, GL_ONE, GL_ZERO))
runStateChange('texture',
               buildTextureSS(),
               buildTextureSS())
runStateChange('depth',
               buildDepthSS(GL_LESS, GL_FALSE),
               buildDepthSS(GL_GREATER, GL_FALSE))
runStateChange('linestipple',
               buildLineSS(False, 1, 0xFFFF),
               buildLineSS(True,  1, 0x5555))
