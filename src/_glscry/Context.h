/* [Begin Copyright Header]
 *
 * GLScry - OpenGL Performance Analysis Tool
 * Copyright (C) 2004-2005  Iowa State University
 * 
 * This software is licensed under the terms of the GNU Lesser Public
 * License, version 2.1, as published by the Free Software Foundation.  
 * See the file COPYRIGHT.txt for details.
 * 
 * Authors:
 *   Chad Austin <aegisk@iastate.edu>
 *   Dirk Reiners <dreiners@iastate.edu>
 *
 * [End Copyright Header] */
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
