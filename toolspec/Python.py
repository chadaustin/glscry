import sys
import os.path

def generate(env):
    if env['PLATFORM'] == 'win32':
        env.Append(LIBS=['python23.lib'])
    else:
        pybase = 'python%s' % sys.version[0:3]
        env.Append(CPPPATH=[os.path.join(sys.prefix, 'include', pybase)],
                   LIBPATH=[os.path.join(sys.prefix, 'lib', pybase, 'config')],
                   LIBS=['lib%s' % pybase])
        if env['PLATFORM'] != 'cygwin':
            env.Append(LIBS=['util'])

def exists(env):
    return 1
