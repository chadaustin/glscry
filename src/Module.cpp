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
using namespace triagara;


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
    

    std::vector<Test*> tests;
    for (int i = 0; i < len(testList); ++i) {
        tests.push_back(extract<Test*>(testList[i]));
    }

    triagara::runTests(filename, tests, runFor, depVar);
}


BOOST_PYTHON_MODULE(_triagara) {
    bindOpenGL();

    def("runTests",      ::runTests);
    def("runTestsRange", ::runTestsRange);

    Test::bind();
    TextureUploadTest::bind();
}
