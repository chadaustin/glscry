#ifdef WIN32
#include <windows.h>  // For IsDebuggerPresent, etc.
#endif


#include <boost/python.hpp>
#include <boost/python/detail/api_placeholder.hpp> // for len()
#include "Run.h"

#include "DepthState.h"
#include "LightState.h"

#include "Geometry.h"

#include "ImmediateTest.h"
#include "IndexedGeometryTest.h"
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

    DEF(GL_BYTE);
    DEF(GL_UNSIGNED_BYTE);
    DEF(GL_SHORT);
    DEF(GL_UNSIGNED_SHORT);
    DEF(GL_INT);
    DEF(GL_UNSIGNED_INT);
    DEF(GL_FLOAT);

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
    DepthState::bind();
    LightState::bind();

    // Geometry generators.

    Array::bind();
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
    IndexedGeometryTest::bind();
}
