#ifndef SCRY_CONTEXT_H
#define SCRY_CONTEXT_H


#include <string>
#include <SDL.h>
#include "glew.h"
#include "GLUtility.h"


namespace scry {

    void pumpMessages();
    void throwSDLError(const std::string& prefix);
    void initializeSDL(int initflags);
    void throwGLEWError(const std::string& prefix, GLenum error);
    void initContext();
    
    Uint64 calculateCoverage(
        GLenum primitiveType,
        GLenum dataType,
        size_t size,
        size_t vertexCount,
        const void* data);

}


#endif
