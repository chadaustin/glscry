def generate(env):
    env.Append(CPPDEFINES=['BOOST_PYTHON_STATIC_LIB'],
               CPPPATH=['$boostIncludes'])
    if env['PLATFORM'] == 'win32':
        env.Append(LIBS=['libboost_python-vc71-mt'])
    else:
        env.Append(LIBS=['boost_python-gcc'])

def exists(env):
    return 1
