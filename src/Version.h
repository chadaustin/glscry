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
#ifndef SCRY_VERSION_H
#define SCRY_VERSION_H


#include "Types.h"


namespace scry {

    #define SCRY_STR_(x) #x
    #define SCRY_STR(x) SCRY_STR_(x)

    #define SCRY_VERSION_MAJOR 0
    #define SCRY_VERSION_MINOR 1
    #define SCRY_VERSION_PATCH 0

    #define SCRY_VERSION                            \
        SCRY_STR(SCRY_VERSION_MAJOR) "."            \
        SCRY_STR(SCRY_VERSION_MINOR) "."            \
        SCRY_STR(SCRY_VERSION_PATCH)

    #define SCRY_BUILD_ID                           \
        SCRY_VERSION ", "                           \
        __DATE__     ", "                           \
        __TIME__

    inline string getVersion() { return SCRY_VERSION; }
    inline string getBuildID() { return SCRY_BUILD_ID; }
    
}


#endif
