from glscry import *
from math import *

def buildStateSet():
    state = TextureState()
    state.texture = Texture()

    stateSet = StateSet()
    stateSet.setState(state)
    return stateSet

TestType = VertexArrayTest
state1 = buildStateSet()
state2 = buildStateSet()
finishAction = FinishAction()

geo = buildGeometry(GL_TRIANGLES, v=defineArray(Array_f, 2))
testNoChange       = TestType("NoChange",       geo)
testChange         = TestType("Change",         geo)
testNoChangeFull   = TestType("NoChangeFull",   geo)
testChangeFull     = TestType("ChangeFull",     geo)
testNoChangeFinish = TestType("NoChangeFinish", geo)
testChangeFinish   = TestType("ChangeFinish",   geo)

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
    testChangeFull,
    testNoChangeFinish,
    testChangeFinish]

power = 1.2
start = floor(log(1) / log(power))
end   = ceil(log(1024) / log(power))
range = uniquePowerRange(start, end, power)

runTestsRange("statechange", testList, 1, "VertexRate", "BatchSize", range)
