import os

SConsignFile()
#CacheDir('cache')



# Options

platform = DefaultEnvironment()['PLATFORM']

defaultBoostIncludes = '/usr/local/include/boost-1_31'
defaultBoostLibs     = '/usr/local/lib'
if platform == 'win32':
    defaultBoostIncludes = Dir('#/third-party/vc7/Boost/include')
    defaultBoostLibs     = Dir('#/third-party/vc7/Boost/lib')

opts = Options('options.cache')
opts.AddOptions(
    PathOption('boostIncludes', 'Directory containing boost header files',
               defaultBoostIncludes),
    PathOption('boostLibs', 'Directory containing boost library files',
               defaultBoostLibs),
    BoolOption('nowarn', 'Disable warnings', 0))

# Base Environment

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
        LINKFLAGS=['/DEBUG'])

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
    env.Append(CCFLAGS=['-Wall', '-O2'],
               CXXFLAGS=['-Wno-non-virtual-dtor'])

Export('env')


# Build Metadata
BuildData = {}
Export('BuildData')


# SConscripts

TargetDirectory = Dir('lib')
BuildDirectory = Dir(os.path.join('build', env['PLATFORM']))
Export('TargetDirectory')

Default(TargetDirectory)

for dir in ['src', 'third-party']:
    SConscript(dirs=[dir], build_dir=BuildDirectory.Dir(dir), duplicate=0)


# MSVS Project

if 'MSVSProject' in env['BUILDERS'].keys():
    env.MSVSProject(target='glscry$MSVSPROJECTSUFFIX',
                    variant='Default',
                    srcs=map(str, BuildData['NativeSources']),
                    buildtarget=BuildData['NativeModule'])
