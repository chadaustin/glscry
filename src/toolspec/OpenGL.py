def generate(env):
    if env['PLATFORM'] in ['cygwin', 'win32']:
        env.Append(LIBS=['opengl32'])
    else:
        env.Append(LIBS=['GL'])

def exists(env):
    return 1
