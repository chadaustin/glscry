#ifdef WIN32
//#include <windows.h>  // For IsDebuggerPresent, etc.
#endif


#include <boost/python.hpp>
#include <boost/python/detail/api_placeholder.hpp> // for len()
#include "Context.h"
#include "Run.h"

#include "ColorBufferState.h"
#include "DepthState.h"
#include "LightState.h"

#include "Geometry.h"

#include "ImmediateTest.h"
#include "DisplayListTest.h"
#include "VertexArrayTest.h"
#include "CompiledVertexArrayTest.h"
#include "VertexBufferObjectTest.h"

#include "CopyPixelTest.h"
#include "DrawPixelTest.h"
#include "ReadPixelTest.h"

#include "TextureUploadTest.h"
#include "TextureMemoryTest.h"

using namespace boost::python;
using namespace scry;


void bindOpenGL() {
    #define DEF(name) scope().attr((#name)) = (name)

    // Data types.
    DEF(GL_BYTE);
    DEF(GL_UNSIGNED_BYTE);
    DEF(GL_SHORT);
    DEF(GL_UNSIGNED_SHORT);
    DEF(GL_INT);
    DEF(GL_UNSIGNED_INT);
    DEF(GL_FLOAT);

    // Primitive types.
    DEF(GL_POINTS);
    DEF(GL_LINES);
    DEF(GL_LINE_STRIP);
    DEF(GL_LINE_LOOP);
    DEF(GL_TRIANGLES);
    DEF(GL_TRIANGLE_STRIP);
    DEF(GL_TRIANGLE_FAN);
    DEF(GL_QUADS);
    DEF(GL_QUAD_STRIP);
    DEF(GL_POLYGON);

    // VBO types.
    DEF(GL_STREAM_DRAW_ARB);
    DEF(GL_STREAM_READ_ARB);
    DEF(GL_STREAM_COPY_ARB);
    DEF(GL_STATIC_DRAW_ARB);
    DEF(GL_STATIC_READ_ARB);
    DEF(GL_STATIC_COPY_ARB);
    DEF(GL_DYNAMIC_DRAW_ARB);
    DEF(GL_DYNAMIC_READ_ARB);
    DEF(GL_DYNAMIC_COPY_ARB);

    // glCopyPixels types.
    DEF(GL_COLOR);
    DEF(GL_DEPTH);
    DEF(GL_STENCIL);

    // Pixel transfer formats.
    DEF(GL_COLOR_INDEX);
    DEF(GL_STENCIL_INDEX);
    DEF(GL_DEPTH_COMPONENT);
    DEF(GL_RED);
    DEF(GL_GREEN);
    DEF(GL_BLUE);
    DEF(GL_ALPHA);
    DEF(GL_RGB);
    DEF(GL_BGR);
    DEF(GL_RGBA);
    DEF(GL_BGRA);
    DEF(GL_LUMINANCE);
    DEF(GL_LUMINANCE_ALPHA);
}


void runTests(const std::string& filename, list testList, float runFor,
              const std::string& depVar) {
    std::vector<TestPtr> tests;
    for (int i = 0; i < len(testList); ++i) {
        tests.push_back(extract<TestPtr>(testList[i]));
    }

    scry::runTests(filename, tests, runFor, depVar);
}


void runTestsRange(const std::string& filename, list testList, float runFor,
                   const std::string& depVar, const std::string& indVar,
                   RangePtr range) {
    std::vector<TestPtr> tests;
    for (int i = 0; i < len(testList); ++i) {
        tests.push_back(extract<TestPtr>(testList[i]));
    }

    scry::runTestsRange(filename, tests, runFor, depVar, indVar, range);
}


void exportGMTL();


BOOST_PYTHON_MODULE(_glscry) {
//    __asm int 3

    initContext();

    exportGMTL();

    bindOpenGL();

    def("runTests",      ::runTests);
    def("runTestsRange", ::runTestsRange);

    // General classes.
    Range::bind();
    LinearRange::bind();
    PowerRange::bind();

    // States.
    State::bind();
    ColorBufferState::bind();
    DepthState::bind();
    LightState::bind();

    // Actions.
    Action::bind();
    ClearAction::bind();

    // Geometry generators.

    bindArrayTypes();
    Geometry::bind();

    // Tests.

    Test::bind();

    TextureUploadTest::bind();
    TextureMemoryTest::bind();

    PixelTransferTest::bind();
    CopyPixelTest::bind();
    DrawPixelTest::bind();
    ReadPixelTest::bind();

    GeometryTest::bind();
    ImmediateTest::bind();
    DisplayListTest::bind();
    VertexArrayTest::bind();
    CompiledVertexArrayTest::bind();
    VertexBufferObjectTest::bind();
}
