#ifndef SCRY_COVERAGE_H
#define SCRY_COVERAGE_H


#include "OpenGL.h"
#include "SDL.h"


namespace scry {

    Uint64 calculateCoverage(
        GLenum primitiveType,
        GLenum dataType,
        size_t size,
        size_t vertexCount,
        const void* data);

}


#endif
