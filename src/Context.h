#ifndef SCRY_CONTEXT_H
#define SCRY_CONTEXT_H


#include <stdexcept>
#include <SDL.h>
#include "glew.h"
#include "Base.h"
#include "GLUtility.h"
#include "ScopeGuard.h"


SCRY_BEGIN_NAMESPACE

inline void pumpMessages() {
    SDL_Event event;
    int result = SDL_PollEvent(&event);
    while (result == 1) {
        if (event.type == SDL_QUIT) {
            exit(EXIT_FAILURE);
        }

        result = SDL_PollEvent(&event);
    }
}


inline void throwSDLError(const std::string& prefix) {
    throw std::runtime_error(prefix + ": " + SDL_GetError());
}


inline void initializeSDL(int initflags) {
    if (SDL_Init(initflags) < 0) {
        throwSDLError("SDL initialization failed");
    }
}


inline void throwGLEWError(const std::string& prefix, GLenum error) {
    throw std::runtime_error(
        prefix + ": " +
        reinterpret_cast<const char*>(glewGetErrorString(error)));
}


// Evil macros.

#ifdef NEAR
#undef NEAR
#endif

#ifdef FAR
#undef FAR
#endif


const int    WIDTH  = 1024;
const int    HEIGHT = 768;
const double NEAR   = -1.0;
const double FAR    = 1.0;


inline void setProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Is this right?
    glOrtho(0, WIDTH, HEIGHT, 0, NEAR, FAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


inline void initContext() {
    initializeSDL(SDL_INIT_NOPARACHUTE | SDL_INIT_VIDEO | SDL_INIT_TIMER);
    
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
}


template<GLenum primitiveType, typename dataType>
struct CoverageCalculator;


// POINTS
template<typename dataType>
struct CoverageCalculator<GL_POINTS, dataType> {
    static size_t calculate(
        size_t size,
        size_t vertexCount,
        const dataType* data
    ) {
        // Assume each point takes up one pixel.
        return vertexCount;
    }
};


// LINES
template<typename dataType>
struct CoverageCalculator<GL_LINES, dataType> {
    static size_t calculate(
        size_t size,
        size_t vertexCount,
        const dataType* data
    ) {
        const dataType* v = data;

        size_t total = 0;
        for (size_t i = 0; (i + 1) < vertexCount; i += 2, v += 2 * size) {
            total += size_t(std::max(fabs(v[0] - v[size]),
                                     fabs(v[1] - v[size + 1])));
        }
        return total;
    }
};


// LINE_STRIP
template<typename dataType>
struct CoverageCalculator<GL_LINE_STRIP, dataType> {
    static size_t calculate(
        size_t size,
        size_t vertexCount,
        const dataType* data
    ) {
        if (vertexCount < 2) {
            return 0;
        }

        typedef gmtl::Vec<dataType, 2> Vec;
        const dataType* v = data;

        size_t total = 0;
        Vec last(v[0], v[1]); v += size;
        for (size_t i = 1; i < vertexCount; ++i, v += size) {
            total += size_t(std::max(fabs(v[0] - last[0]),
                                     fabs(v[1] - last[1])));
            last = Vec(v[0], v[1]);
        }
        return total;
    }
};


// LINE_LOOP
template<typename dataType>
struct CoverageCalculator<GL_LINE_LOOP, dataType> {
    static size_t calculate(
        size_t size,
        size_t vertexCount,
        const dataType* data
    ) {
        if (vertexCount < 2) {
            return 0;
        }

        typedef gmtl::Vec<dataType, 2> Vec;
        const dataType* v = data;

        size_t total = 0;
        Vec last(v[0], v[1]);
        Vec first(last);
        for (size_t i = 1; i < vertexCount; ++i, v += size) {
            total += size_t(std::max(fabs(v[0] - last[0]),
                                     fabs(v[1] - last[1])));
            last = Vec(v[0], v[1]);
        }
        total += size_t(std::max(fabs(first[0] - last[0]),
                                 fabs(first[1] - last[1])));
        return total;
    }
};


template<typename dataType>
size_t getTriangleArea(gmtl::Vec<dataType, 2> a,
                       gmtl::Vec<dataType, 2> b,
                       gmtl::Vec<dataType, 2> c
) {
    // http://www.btinternet.com/~se16/hgb/triangle.htm    
    float ab = b[0] * a[1] - a[0] * b[1];
    float bc = c[0] * b[1] - b[0] * c[1];
    float ac = a[0] * c[1] - c[0] * a[1];
    return size_t(fabs(ab + bc + ac) / 2);
}


// TRIANGLES
template<typename dataType>
struct CoverageCalculator<GL_TRIANGLES, dataType> {
    static size_t calculate(
        size_t size,
        size_t vertexCount,
        const dataType* data
    ) {
        typedef gmtl::Vec<dataType, 2> Vec;
        const dataType* v = data;

        size_t total = 0;
        for (size_t i = 0; (i + 2) < vertexCount; i += 3, v += size * 3) {
            total += getTriangleArea(
                Vec(v[size * 0], v[size * 0 + 1]),
                Vec(v[size * 1], v[size * 1 + 1]),
                Vec(v[size * 2], v[size * 2 + 1]));
        }
        return total;
    }
};


// TRIANGLE_STRIP
template<typename dataType>
struct CoverageCalculator<GL_TRIANGLE_STRIP, dataType> {
    static size_t calculate(
        size_t size,
        size_t vertexCount,
        const dataType* data
    ) {
        typedef gmtl::Vec<dataType, 2> Vec;
        const dataType* v = data;

        if (vertexCount < 3) {
            return 0;
        }

        Vec v0(v[0], v[1]); v += size;
        Vec v1(v[0], v[1]); v += size;

        size_t total = 0;
        for (size_t i = 2; i < vertexCount; i += 3, v += size * 3) {
            Vec v2(v[0], v[1]);
            total += getTriangleArea(v0, v1, v2);
            v0 = v1;
            v1 = v2;
        }
        return total;
    }
};


// TRIANGLE_FAN
template<typename dataType>
struct CoverageCalculator<GL_TRIANGLE_FAN, dataType> {
    static size_t calculate(
        size_t size,
        size_t vertexCount,
        const dataType* data
    ) {
        if (vertexCount < 2) {
            return 0;
        }

        typedef gmtl::Vec<dataType, 2> Vec;
        const dataType* v = data;

        Vec first(v[0], v[1]); v += size;
        Vec last (v[0], v[1]); v += size;

        size_t total = 0;
        for (size_t i = 1; i < vertexCount; ++i, v += size) {
            Vec current(v[0], v[1]);
            total += getTriangleArea(first, last, current);
            last = current;
        }
        return total;
    }
};


// QUADS
template<typename dataType>
struct CoverageCalculator<GL_QUADS, dataType> {
    static size_t calculate(
        size_t size,
        size_t vertexCount,
        const dataType* data
    ) {
        typedef gmtl::Vec<dataType, 2> Vec;
        const dataType* v = data;

        size_t total = 0;
        for (size_t i = 0; (i + 3) < vertexCount; i += 4) {
            Vec v1(v[0], v[1]); v += size;
            Vec v2(v[0], v[1]); v += size;
            Vec v3(v[0], v[1]); v += size;
            Vec v4(v[0], v[1]); v += size;
            total += getTriangleArea(v1, v2, v3);
            total += getTriangleArea(v1, v3, v4);
        }
        return total;
    }
};


// QUAD_STRIP
template<typename dataType>
struct CoverageCalculator<GL_QUAD_STRIP, dataType> {
    static size_t calculate(
        size_t size,
        size_t vertexCount,
        const dataType* data
    ) {
        if (vertexCount < 4) {
            return 0;
        }

        typedef gmtl::Vec<dataType, 2> Vec;
        const dataType* v = data;

        Vec v1(v[0], v[1]); v += size;
        Vec v2(v[0], v[1]); v += size;

        size_t total = 0;
        for (size_t i = 2; (i + 1) < vertexCount; i += 2) {
            Vec v3(v[0], v[1]); v += size;
            Vec v4(v[0], v[1]); v += size;
            total += getTriangleArea(v1, v2, v3);
            total += getTriangleArea(v1, v3, v4);
            v1 = v3;
            v2 = v4;
        }
        return total;
    }
};


// POLYGON
template<typename dataType>
struct CoverageCalculator<GL_POLYGON, dataType> {
    static size_t calculate(
        size_t size,
        size_t vertexCount,
        const dataType* data
    ) {
        if (vertexCount < 3) {
            return 0;
        }

        typedef gmtl::Vec<dataType, 2> Vec;
        const dataType* v = data;
        Vec first(v[0], v[1]); v += size;
        Vec last (v[0], v[1]); v += size;

        size_t total = 0;
        for (size_t i = 2; i < vertexCount; ++i) {
            Vec current(v[0], v[1]); v += size;
            total += getTriangleArea(first, last, current);
            last = current;
        }
        return total;
    }
};


// Stupid hack so we can partially specialize "functions".
template<GLenum primitiveType, typename dataType>
size_t calculateCoverage(
    size_t size,
    size_t vertexCount,
    const void* data
) {
    return CoverageCalculator<primitiveType, dataType>::calculate(
        size, vertexCount, static_cast<const dataType*>(data));
}


template<GLenum primitiveType>
size_t calculateCoverage(
    GLenum dataType,
    size_t size,
    size_t vertexCount,
    const void* data
) {
#define SCRY_SPECIALIZE_DATA_TYPE(type)                         \
    case type: return calculateCoverage<primitiveType,          \
        typename GLType<type>::Result>(size, vertexCount, data)

    switch (dataType) {
        SCRY_SPECIALIZE_DATA_TYPE(GL_FLOAT);
        SCRY_SPECIALIZE_DATA_TYPE(GL_DOUBLE);
        default: throw std::runtime_error("Unknown data type");
    }
}



inline size_t calculateCoverage(
    GLenum primitiveType,
    GLenum dataType,
    size_t size,
    size_t vertexCount,
    const void* data
) {
#define SCRY_SPECIALIZE_PRIMITIVE_TYPE(type)      \
    case type: return calculateCoverage<type>(dataType, size, vertexCount, data)

    switch (primitiveType) {
        SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_POINTS);
        SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_LINES);
        SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_LINE_STRIP);
        SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_LINE_LOOP);
        SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_TRIANGLES);
        SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_TRIANGLE_STRIP);
        SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_TRIANGLE_FAN);
        SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_QUADS);
        SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_QUAD_STRIP);
        SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_POLYGON);
        default: throw std::runtime_error("Invalid primitive type in calculateCoverage");
    }
}


SCRY_END_NAMESPACE


#endif
