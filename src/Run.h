#ifndef SCRY_RUN_H
#define SCRY_RUN_H


#include <fstream>
#include <SDL.h>
#include "Context.h"
#include "glew.h"
#include "Range.h"
#include "ScopeGuard.h"
#include "Test.h"


SCRY_BEGIN_NAMESPACE


const int    WIDTH  = 1024;
const int    HEIGHT = 768;
const double NEAR   = -1.0;
const double FAR    = 1.0;


void output(std::ostream& os, TestPtr test, const ResultSet& results,
            const std::string& depVar) {
    std::vector<ResultDesc> descs;
    test->getResultDescs(descs);
    SCRY_ASSERT(descs.size() == results.size());

    int resultIndex = -1;
    for (size_t i = 0; i < descs.size(); ++i) {
        if (descs[i].name == depVar) {
            resultIndex = i;
            break;
        }
    }
    if (resultIndex == -1) {
        throw std::runtime_error("Test has no such result");
    }
    
    os << results[resultIndex] << " ";

    std::cout << "  " << test->getName() << ": ";

    std::cout << descs[resultIndex].name << " = "
              << Uint64(results[resultIndex]) << " "
              << descs[resultIndex].units << std::endl;
}

void flip() {
    SDL_GL_SwapBuffers();
}

void betweenTests() {
    glClear(GL_COLOR_BUFFER_BIT);
    pumpMessages();
    flip();
}

void runTests(const std::string& filename, std::vector<TestPtr> testList,
              float runFor, const std::string& depVar) {
    
    std::ofstream of(filename.c_str());
    if (!of) {
        throw std::runtime_error("Could not open " + filename);
    }

    for (size_t i = 0; i < testList.size(); ++i) {
        betweenTests();

        TestPtr test = testList[i];
        if (test->isSupported()) {
            ResultSet results = test->run(runFor);
            output(of, test, results, depVar);
        } else {
            // output a zero ?
        }
    }
    of << std::endl;
}


void runTestsRange(const std::string& filename, std::vector<TestPtr> testList,
                   float runFor, const std::string& depVar,
                   const std::string& indVar, RangePtr range) {
    
    std::ofstream of(filename.c_str());
    if (!of) {
        throw std::runtime_error("Could not open " + filename);
    }

    size_t indValue;
    while (range->next(indValue)) {
        for (size_t i = 0; i < testList.size(); ++i) {
            betweenTests();

            TestPtr test = testList[i];
            test->setProperty(indVar, indValue);
            if (test->isSupported()) {
                ResultSet results = test->run(runFor);
                output(of, test, results, depVar);
            } else {
                // output a zero
            }
        }
        of << std::endl;
    }
}


void throwSDLError(const std::string& prefix) {
    throw std::runtime_error(prefix + ": " + SDL_GetError());
}

void initializeSDL(int initflags) {
    if (SDL_Init(initflags) < 0) {
        throwSDLError("SDL initialization failed");
    }
}

void throwGLEWError(const std::string& prefix, GLenum error) {
    throw std::runtime_error(
        prefix + ": " +
        reinterpret_cast<const char*>(glewGetErrorString(error)));
}


void setProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Is this right?
    glOrtho(0, WIDTH, HEIGHT, 0, NEAR, FAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void run(boost::python::object test) {
    initializeSDL(SDL_INIT_NOPARACHUTE | SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SCRY_ON_BLOCK_EXIT(SDL_Quit);
    
    // define our minimum requirements for the GL window
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,   16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    int mode = SDL_OPENGL | SDL_ANYFORMAT;
    const bool fullscreen = false;
    if (fullscreen) {
        mode |= SDL_FULLSCREEN;
    }

    // If we set this before opening the window, the window has
    // this caption.
    SDL_WM_SetCaption("GLScry", 0);

    /**
     * @note SDL does silly things when the created window is larger
     * than the desktop.
     */
    if (!SDL_SetVideoMode(WIDTH, HEIGHT, 32, mode)) {
        throwSDLError("Setting video mode failed");
    }

    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        throwGLEWError("Initializing GLEW failed", glewError);
    }

    setProjection();

    SDL_ShowCursor(SDL_DISABLE);

    test();

    //testBatchSizes("zeroes.data",          Zeroes(),         0, 14);
    //testBatchSizes("small_triangles.data", SmallTriangles(), 0, 14);
    //testPixelTransfers();
    //testTextureUploads();
    //testVertexCache();
    //testLights();
    //testHeirarchialZBuffer();
}


SCRY_END_NAMESPACE


#endif
