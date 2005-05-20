from glscry import *
from math import *

runFor = 4
batchSize = 1

TestType = VertexArrayTest
finishAction = FinishAction()
v = defineArray(Array_f, 2, (5, 5) + (5, 6) + (6, 6))
geo = buildGeometry((GL_TRIANGLES, batchSize), v=defineArray(Array_f, 2))


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

def buildVertexShaderSS(source):
    shaders = ShaderList()
    shaders[:] = [VertexShader(source)]
    program = Program(shaders)
    state = ShaderState(program)
    return StateSet(state)

def buildFragmentShaderSS(source):
    shaders = ShaderList()
    shaders[:] = [FragmentShader(source)]
    program = Program(shaders)
    state = ShaderState(program)
    return StateSet(state)



nochange    =[]
change      =[]
nochangefull=[]
changefull  =[]

def testStateChange(name, ss1, ss2):
    testNoChange       = TestType(name, geo)
    testChange         = TestType(name, geo)
    testNoChangeFull   = TestType(name, geo)
    testChangeFull     = TestType(name, geo)
    testNoChangeFinish = TestType(name, geo)
    testChangeFinish   = TestType(name, geo)

    for t in [testNoChange, testNoChangeFull, testNoChangeFinish]:
        t.addStateSet(ss1)

    for t in [testChange, testChangeFull, testChangeFinish]:
        t.addStateSet(ss1)
        t.addStateSet(ss2)

    for t in [testNoChangeFull, testChangeFull]:
        t.fullStateSwitch = True

    for t in [testNoChangeFinish, testChangeFinish]:
        t.addAction(finishAction)

    nochange    .append(testNoChange)
    change      .append(testChange)
    nochangefull.append(testNoChangeFull)
    changefull  .append(testChangeFull)

testStateChange('blend',
               buildBlendSS(True, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA),
               buildBlendSS(False, GL_ONE, GL_ZERO))
testStateChange('texture',
               buildTextureSS(),
               buildTextureSS())
testStateChange('depth',
               buildDepthSS(GL_LESS, GL_FALSE),
               buildDepthSS(GL_GREATER, GL_FALSE))
testStateChange('linestipple',
               buildLineSS(False, 1, 0xFFFF),
               buildLineSS(True,  1, 0x5555))

if ShaderState.isSupported():
    if VertexShader.isSupported():
        testStateChange('vertex_shader',
                       buildVertexShaderSS('void main() { gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; }'),
                       buildVertexShaderSS('void main() { gl_Position = ftransform(); }'))

    if FragmentShader.isSupported():
        testStateChange('fragment_shader',
                       buildFragmentShaderSS('void main() { gl_FragColor = vec4(1, 1, 1, 1); }'),
                       buildFragmentShaderSS('void main() { gl_FragColor = vec4(0, 0, 0, 1); }'))

    # Uniforms
    if VertexShader.isSupported():
        source = """\
uniform vec4 offset;
void main() {
  gl_Position = gl_ModelViewProjectionMatrix * (gl_Vertex + offset);
}
"""
        
        shaders = ShaderList()
        shaders[:] = [VertexShader(source)]
        program = Program(shaders)

        ss1 = ShaderState(program)
        ss1.setUniform4f('offset', Vec4f(0, 0, 0, 0))
    
        ss2 = ShaderState(program)
        ss2.setUniform4f('offset', Vec4f(1, 1, 1, 0))
    
        testStateChange('uniform', StateSet(ss1), StateSet(ss2))


results = [
    runTests('No Change',      nochange, runFor),
    runTests('Change',         change, runFor),
    runTests('No Change Full', nochangefull, runFor),
    runTests('Change Full',    changefull, runFor) ]

generateGraph('statechange', results, "VertexRate")
