import os

platform = DefaultEnvironment()['PLATFORM']

defaultBoostIncludes = '/usr/local/include/boost-1_31'
if platform == 'win32':
    defaultBoostIncludes = Dir('#/third-party/vc7/include')

opts = Options('options.cache')
opts.AddOptions(
    PathOption('boostIncludes', 'Directory containing boost header files',
               defaultBoostIncludes))

env = Environment(
    tools=['default', 'SDL', 'OpenGL', 'BoostPython', 'Python'],
    toolpath=['toolspec'],
    options=opts)

env.Append(CPPPATH=['#/third-party/all'])
if env.subst('$CXX') == 'cl':
    env.Append(
        CXXFLAGS=['/GX', '/GR', '/MD', '/Zi'],
        LINKFLAGS=['/DEBUG'],
        CPPPATH=['#/third-party/vc7/include'],
        LIBPATH=['#/third-party/vc7/lib'])

Help(opts.GenerateHelpText(env))
opts.Save('options.cache', env)

if env['PLATFORM'] in ['cygwin', 'win32']:
    env.Append(CPPDEFINES=['WIN32', '_WIN32'])

if env.subst('$CC') == 'gcc':
    env.Append(CCFLAGS=['-O2', '-Wall'])

env.Append(CPPDEFINES=['GLEW_STATIC'])

modulename = env.subst('_glscry$SHLIBSUFFIX')
module = env.SharedLibrary(File(modulename), Split("""
    src/Module.cpp
    src/glew.c
    src/Timer.cpp

    src/Test.cpp

    src/TextureUploadTest.cpp

    src/PixelTransferTest.cpp
    src/CopyPixelTest.cpp
    src/DrawPixelTest.cpp
    src/ReadPixelTest.cpp
"""))


env = DefaultEnvironment()
if 'MSVSProject' in env['BUILDERS'].keys():
    env.MSVSProject(target='glscry$MSVSPROJECTSUFFIX',
                    variant='Default',
                    buildtarget=module)
