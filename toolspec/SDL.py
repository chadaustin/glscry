import os

def generate(env):
    if env['PLATFORM'] == 'cygwin':
        prefix = os.popen('sdl-config --prefix').read()[0:-1]
        env.Append(CPPPATH = os.path.join(prefix, 'include/SDL'),
                   CPPDEFINES = ['main=SDL_main', 'WIN32'],
                   LIBPATH = os.path.join(prefix, 'lib'),
                   LIBS = ['SDL', 'SDLmain'])
    elif env['PLATFORM'] == 'win32':
        env.Append(CPPPATH=['#/third-party/vc7/SDL/include'],
                   LIBPATH=['#/third-party/vc7/SDL/lib'],
                   LIBS=['SDL', 'SDLmain'])
    else:
        env.ParseConfig('sdl-config --cflags --libs')
        if env['PLATFORM'] == 'irix':
            env.Append(CPPDEFINES=['SDL_HAS_64BIT_TYPE=long long'])

def exists(env):
    return env.WhereIs('sdl-config')
