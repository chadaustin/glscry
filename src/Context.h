#ifndef SCRY_CONTEXT_H
#define SCRY_CONTEXT_H


#include <string>
#include "OpenGL.h"


namespace scry {

    void pumpMessages();
    void throwSDLError(const std::string& prefix);
    void initializeSDL(int initflags);
    void throwGLEWError(const std::string& prefix, GLenum error);
    void initContext();
    
    void flip();
    void betweenTests();
    void bindContext();

}


#endif
