#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <boost/python.hpp>
#include "Context.h"
#include "glew.h"
#include "GeometryGenerator.h"
#include "GeometryTest.h"
#include "GLUtility.h"
#include "Range.h"
#include "Run.h"

#include "DepthState.h"
#include "LightState.h"

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


SCRY_BEGIN_NAMESPACE


void testBatchSizes(const std::string& filename, const GeometryGenerator& gen,
                      int beginRange, int endRange) {
    std::vector<Test*> testList;
    testList.push_back(new ImmediateTest(&gen));
    testList.push_back(new DisplayListTest(&gen));
    testList.push_back(new VertexArrayTest(&gen));
    testList.push_back(new CompiledVertexArrayTest(&gen));
    testList.push_back(new VertexBufferObjectTest(&gen));

    Range& range = PowerRange(beginRange, endRange).get();
    runTestsRange(filename, testList, 0.2f, "TriangleRate",
                  "BatchSize", range);
}


void testPixelTransfers() {
    std::vector<Test*> testList;
    testList.push_back(new CopyPixelTest);
    testList.push_back(new DrawPixelTest);
    testList.push_back(new ReadPixelTest);

    runTests("pixel.data", testList, 1.0f, "PixelRate");
}


void testTextureUploads() {
    TextureUploadTest* test1 = new TextureUploadTest;
    TextureUploadTest* test2 = new TextureUploadTest;
    test2->setWidth(512);
    test2->setHeight(512);
    TextureUploadTest* test3 = new TextureUploadTest;
    test3->setType(GL_BYTE);
    TextureUploadTest* test4 = new TextureUploadTest;
    test4->setType(GL_UNSIGNED_SHORT);
    TextureUploadTest* test5 = new TextureUploadTest;
    test5->setType(GL_SHORT);
    TextureUploadTest* test6 = new TextureUploadTest;
    test6->setType(GL_UNSIGNED_INT);
    TextureUploadTest* test7 = new TextureUploadTest;
    test7->setType(GL_INT);
    TextureUploadTest* test8 = new TextureUploadTest;
    test8->setType(GL_FLOAT);

    std::vector<Test*> testList;
    testList.push_back(test1);
    testList.push_back(test2);
    testList.push_back(test3);
    testList.push_back(test4);
    testList.push_back(test5);
    testList.push_back(test6);
    testList.push_back(test7);
    testList.push_back(test8);

    runTests("upload.data", testList, 1.0f, "PixelRate");
}


void testVertexCache() {
    Zeroes z;

    std::vector<Test*> testList;
    testList.push_back(new IndexedGeometryTest(&z));
    runTestsRange("vcache.data", testList, 1.0f, "TriangleRate",
                  "BatchSize", PowerRange(1, 16).get());
}


void testLights() {
    std::vector<Test*> testList;
    for (size_t i = 0; i < 8; ++i) {
        LightState* light = new LightState;
        for (size_t j = 0; j < i; ++j) {
            light->useLight(j, true);
            light->setAmbient(j, Vec4f(0.5f, 0.5f, 0.5f, 1.0f));
        }
        SmallTriangles gen;
        Test* test = new VertexArrayTest(&gen);
        test->setState(light);
        testList.push_back(test);
    }

    runTests("light.data", testList, 1.0f, "TriangleRate");
}


void testHeirarchialZBuffer() {
    Zeroes genFrontToBack;
    Zeroes genBackToFront;

    GeometryTest* frontToBack = new VertexArrayTest(&genFrontToBack);
    GeometryTest* backToFront = new VertexArrayTest(&genBackToFront);

    std::vector<Test*> testList;
    testList.push_back(frontToBack);
    testList.push_back(backToFront);
    runTests("heir_z.data", testList, 1.0f, "TriangleRate");
}


SCRY_END_NAMESPACE


int main(int /*argc*/, char** /*argv*/) {
    try {
        //scry::run();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
#if 0
    catch (...) {
        // This catches _everything_, including null pointer accesses
        // and div by zero.
    }
#endif
    return EXIT_FAILURE;
}


#if defined(WIN32) && !defined(_CONSOLE)

    #include <windows.h>

    #ifdef __CYGWIN__
    extern "C" __declspec(dllimport) int __argc;
    extern "C" __declspec(dllimport) char* __argv[];
    #endif

    int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
        return main(__argc, __argv);
    }

#endif
