import os

SConsignFile()

platform = DefaultEnvironment()['PLATFORM']

defaultBoostIncludes = '/usr/local/include/boost-1_31'
defaultBoostLibs     = '/usr/local/lib'
if platform == 'win32':
    defaultBoostIncludes = Dir('#/third-party/vc7/include')
    defaultBoostLibs     = Dir('#/third-party/vc7/lib')

opts = Options('options.cache')
opts.AddOptions(
    PathOption('boostIncludes', 'Directory containing boost header files',
               defaultBoostIncludes),
    PathOption('boostLibs', 'Directory containing boost library files',
               defaultBoostLibs),
    BoolOption('nowarn', 'Disable warnings', 0))

env = Environment(
    tools=['default', 'SDL', 'OpenGL', 'BoostPython', 'Python'],
    toolpath=['toolspec'],
    options=opts)

if env['PLATFORM'] != 'win32':
    env['ENV'] = os.environ

Help(opts.GenerateHelpText(env))
opts.Save('options.cache', env)

env.Append(CPPPATH=['#/third-party/all'])
if env.subst('$CXX') == 'cl':
    env.Append(
        CPPDEFINES=['_WIN32_WINNT=0x0400'],
        CXXFLAGS=['/GX', '/GR', '/MD', '/Z7'],
        LINKFLAGS=['/DEBUG'],
        CPPPATH=['#/third-party/vc7/include'],
        LIBPATH=['#/third-party/vc7/lib'])

if env['nowarn']:
    env.Append(CCFLAGS=['-w'])

if env['PLATFORM'] in ['cygwin', 'win32']:
    env.Append(CPPDEFINES=['WIN32', '_WIN32'])

# If using GCC, deal with ld O(n^2) algorithm.
if env['CXX'][:3] == 'g++' and env.WhereIs('objcopy'):
    env['CXXCOM']   = [env['CXXCOM'],   'objcopy --set-section-flags .debug_str=contents,debug $TARGET']
    env['SHCXXCOM'] = [env['SHCXXCOM'], 'objcopy --set-section-flags .debug_str=contents,debug $TARGET']

env.Append(CPPDEFINES=['GLEW_STATIC'])
env.Append(CPPPATH=['src/gmtl-python'])

if env.subst('$CC') == 'gcc':
    env.Append(CCFLAGS=['-Wall', '-O2'])

Export('env')
  
module = SConscript(dirs=['src'])

if 'MSVSProject' in env['BUILDERS'].keys():
    env.MSVSProject(target='glscry$MSVSPROJECTSUFFIX',
                    variant='Default',
                    buildtarget=module)
