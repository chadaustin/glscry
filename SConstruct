import os

SConsignFile()

platform = DefaultEnvironment()['PLATFORM']

defaultBoostIncludes = '/usr/local/include/boost-1_31'
if platform == 'win32':
    defaultBoostIncludes = Dir('#/third-party/vc7/include')

opts = Options('options.cache')
opts.AddOptions(
    PathOption('boostIncludes', 'Directory containing boost header files',
               defaultBoostIncludes))

env = Environment(
    tools=['default', 'SDL', 'OpenGL', 'BoostPython', 'Python'],
    toolpath=['toolspec'],
    options=opts)

env.Append(CPPPATH=['#/third-party/all'])
if env.subst('$CXX') == 'cl':
    env.Append(
        CXXFLAGS=['/GX', '/GR', '/MD', '/Z7'],
        LINKFLAGS=['/DEBUG'],
        CPPPATH=['#/third-party/vc7/include'],
        LIBPATH=['#/third-party/vc7/lib'])

Help(opts.GenerateHelpText(env))
opts.Save('options.cache', env)

if env['PLATFORM'] in ['cygwin', 'win32']:
    env.Append(CPPDEFINES=['WIN32', '_WIN32'])

if env.subst('$CC') == 'gcc':
    env.Append(CCFLAGS=['-O2', '-Wall'])

env.Append(CPPDEFINES=['GLEW_STATIC'])
env.Append(CPPPATH=['src/gmtl-python'])

sources = Split("""
    Module.cpp
    glew.c
    Range.cpp
    Timer.cpp

    GeometryGenerator.cpp

    State.cpp
    DepthState.cpp
    LightState.cpp

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
    IndexedGeometryTest.cpp
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


modulename = env.subst('_glscry$SHLIBSUFFIX')
module = env.SharedLibrary(
    File(modulename),
    [os.path.join('src', s) for s in sources] +
    [os.path.join('src/gmtl-python', s) for s in gmtlPythonSources])


env = DefaultEnvironment()
if 'MSVSProject' in env['BUILDERS'].keys():
    env.MSVSProject(target='glscry$MSVSPROJECTSUFFIX',
                    variant='Default',
                    buildtarget=module)
