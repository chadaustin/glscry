import os

SConsignFile()

platform = DefaultEnvironment()['PLATFORM']

defaultBoostIncludes = '/usr/local/include/boost-1_31'
if platform == 'win32':
    defaultBoostIncludes = Dir('#/third-party/vc7/include')

opts = Options('options.cache')
opts.AddOptions(
    PathOption('boostIncludes', 'Directory containing boost header files',
               defaultBoostIncludes),
    BoolOption('nowarn', 'Disable warnings', 0))

env = Environment(
    ENV=os.environ,
    tools=['default', 'SDL', 'OpenGL', 'BoostPython', 'Python'],
    toolpath=['toolspec'],
    options=opts)

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

sources = Split("""
    Module.cpp

    Action.cpp
    Context.cpp
    glew.c
    GLUtility.cpp
    Range.cpp
    Run.cpp
    Timer.cpp

    Array.cpp
    Geometry.cpp

    State.cpp
    ColorBufferState.cpp
    DepthState.cpp
    LightState.cpp
    MaterialState.cpp
    TextureState.cpp

    Test.cpp

    TextureUploadTest.cpp
    TextureMemoryTest.cpp

    PixelTransferTest.cpp
    CopyPixelTest.cpp
    DrawPixelTest.cpp
    ReadPixelTest.cpp

    GeometryTest.cpp
    ImmediateTest.cpp
    DisplayListTest.cpp
    VertexArrayTest.cpp
    CompiledVertexArrayTest.cpp
    VertexBufferObjectTest.cpp
""")

gmtlPythonSources = Split("""
    _AABox_double.cpp
    _AABox_float.cpp
    _AxisAngle_double.cpp
    _AxisAngle_float.cpp
    _Coord_gmtl_Vec_double_3_gmtl_AxisAngle_double.cpp
    _Coord_gmtl_Vec_double_3_gmtl_EulerAngle_double_gmtl_XYZ.cpp
    _Coord_gmtl_Vec_double_3_gmtl_EulerAngle_double_gmtl_ZXY.cpp
    _Coord_gmtl_Vec_double_3_gmtl_EulerAngle_double_gmtl_ZYX.cpp
    _Coord_gmtl_Vec_double_3_gmtl_Quat_double.cpp
    _Coord_gmtl_Vec_double_4_gmtl_AxisAngle_double.cpp
    _Coord_gmtl_Vec_double_4_gmtl_EulerAngle_double_gmtl_XYZ.cpp
    _Coord_gmtl_Vec_double_4_gmtl_EulerAngle_double_gmtl_ZXY.cpp
    _Coord_gmtl_Vec_double_4_gmtl_EulerAngle_double_gmtl_ZYX.cpp
    _Coord_gmtl_Vec_double_4_gmtl_Quat_double.cpp
    _Coord_gmtl_Vec_float_3_gmtl_AxisAngle_float.cpp
    _Coord_gmtl_Vec_float_3_gmtl_EulerAngle_float_gmtl_XYZ.cpp
    _Coord_gmtl_Vec_float_3_gmtl_EulerAngle_float_gmtl_ZXY.cpp
    _Coord_gmtl_Vec_float_3_gmtl_EulerAngle_float_gmtl_ZYX.cpp
    _Coord_gmtl_Vec_float_3_gmtl_Quat_float.cpp
    _Coord_gmtl_Vec_float_4_gmtl_AxisAngle_float.cpp
    _Coord_gmtl_Vec_float_4_gmtl_EulerAngle_float_gmtl_XYZ.cpp
    _Coord_gmtl_Vec_float_4_gmtl_EulerAngle_float_gmtl_ZXY.cpp
    _Coord_gmtl_Vec_float_4_gmtl_EulerAngle_float_gmtl_ZYX.cpp
    _Coord_gmtl_Vec_float_4_gmtl_Quat_float.cpp
    _EulerAngle_float_gmtl_XYZ.cpp
    _EulerAngle_float_gmtl_ZXY.cpp
    _EulerAngle_float_gmtl_ZYX.cpp
    _LineSeg_double.cpp
    _LineSeg_float.cpp
    _Matrix_float_3_3.cpp
    _Matrix_float_4_4.cpp
    _Plane_double.cpp
    _Plane_float.cpp
    _Point_float_2.cpp
    _Point_float_3.cpp
    _Point_int_2.cpp
    _Point_int_3.cpp
    _Quat_double.cpp
    _Quat_float.cpp
    _Ray_double.cpp
    _Ray_float.cpp
    _Sphere_double.cpp
    _Sphere_float.cpp
    _Tri_double.cpp
    _Tri_float.cpp
    _Tri_int.cpp
    _VecBase_double_2.cpp
    _VecBase_double_3.cpp
    _VecBase_double_4.cpp
    _VecBase_float_2.cpp
    _VecBase_float_3.cpp
    _VecBase_float_4.cpp
    _VecBase_int_2.cpp
    _VecBase_int_3.cpp
    _VecBase_int_4.cpp
    _Vec_double_3.cpp
    _Vec_double_4.cpp
    _Vec_float_3.cpp
    _Vec_float_4.cpp
    _Vec_int_3.cpp
    _Vec_int_4.cpp
    _gmtl_AABoxOps_h.cpp
    _gmtl_AxisAngleOps_h.cpp
    _gmtl_Containment_h.cpp
    _gmtl_CoordOps_h.cpp
    _gmtl_Defines_h.cpp
    _gmtl_EulerAngleOps_h.cpp
    _gmtl_Generate_h.cpp
    _gmtl_LineSegOps_h.cpp
    _gmtl_Math_h.cpp
    _gmtl_MatrixOps_h.cpp
    _gmtl_PlaneOps_h.cpp
    _gmtl_QuatOps_h.cpp
    _gmtl_SphereOps_h.cpp
    _gmtl_TriOps_h.cpp
    _gmtl_VecOps_h.cpp
    _gmtl_Xforms_h.cpp
    _gmtl_intersect_wrappers_h.cpp
    _gmtl_wrappers_h.cpp
    gmtl.cpp
""")


# When building gmtl-python in Cygwin with g++, the linker tries to allocate
# over 4 GB of RAM if debugging symbols are allocated.
gmtlPythonEnv = env.Copy()
if gmtlPythonEnv['PLATFORM'] == 'cygwin':
    if '-g' in (gmtlPythonEnv.get('CCFLAGS') or []):
        gmtlPythonEnv['CCFLAGS'].remove('-g')

modulename = env.subst('_glscry$SHLIBSUFFIX')
module = env.SharedLibrary(
    File(modulename),
    [os.path.join('src', s) for s in sources] +
    [gmtlPythonEnv.SharedObject(os.path.join('src/gmtl-python', s)) for s in gmtlPythonSources])


env = DefaultEnvironment()
if 'MSVSProject' in env['BUILDERS'].keys():
    env.MSVSProject(target='glscry$MSVSPROJECTSUFFIX',
                    variant='Default',
                    buildtarget=module)
