import os

def generate(env):
    if env['PLATFORM'] == 'cygwin':
        prefix = os.popen('sdl-config --prefix').read()[0:-1]
        env.Append(CPPPATH = os.path.join(prefix, 'include/SDL'),
                   CPPDEFINES = ['main=SDL_main', 'WIN32'],
                   LIBPATH = os.path.join(prefix, 'lib'),
                   LIBS = ['SDL', 'SDLmain'])
    elif env['PLATFORM'] == 'win32':
        env.Append(LIBS=['SDL', 'SDLmain'])
    else:
        env.ParseConfig('sdl-config --cflags --libs')

def exists(env):
    return env.WhereIs('sdl-config')
