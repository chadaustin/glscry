#include <boost/python.hpp>
#include <boost/python/detail/api_placeholder.hpp> // for len()
#include "Run.h"

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
}


void runTests(const std::string& filename, list testList, float runFor,
              const std::string& depVar) {
    std::vector<TestPtr> tests;
    for (int i = 0; i < len(testList); ++i) {
        tests.push_back(extract<TestPtr>(testList[i]));
    }

    scry::runTests(filename, tests, runFor, depVar);
}


BOOST_PYTHON_MODULE(_glscry) {
    bindOpenGL();

    def("run",            ::run);
    def("runTests_",      ::runTests);
    def("runTestsRange_", ::runTestsRange);

    Test::bind();

    TextureUploadTest::bind();

    PixelTransferTest::bind();
    CopyPixelTest::bind();
    DrawPixelTest::bind();
    ReadPixelTest::bind();
}
