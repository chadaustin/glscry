import sys
import os.path

def generate(env):
    pybase = 'python%s' % sys.version[0:3]
    env.Append(CPPPATH=[os.path.join(sys.prefix, 'include', pybase)],
               LIBPATH=[os.path.join(sys.prefix, 'lib', pybase, 'config')],
               LIBS=['lib%s' % pybase])
    if env['PLATFORM'] not in ['cygwin', 'win32']:
        env.Append(LIBS=['util'])

def exists(env):
    return 1
