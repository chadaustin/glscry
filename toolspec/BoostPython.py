def generate(env):
    env.Append(CPPDEFINES=['BOOST_PYTHON_STATIC_LIB'],
               CPPPATH=['$boostIncludes'],
               LIBPATH=['$boostLibs'])
    if env['PLATFORM'] == 'win32':
        env.Append(LIBS=['libboost_python-vc71-mt'])
    elif env['PLATFORM'] == 'irix':
        env.Append(CPPPATH=['$boostIncludes/boost/compatibility/cpp_c_headers'],
                   LIBS=['boost_python-mp'])
    else:
        env.Append(LIBS=['boost_python-gcc'])

def exists(env):
    return 1
