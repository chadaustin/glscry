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
#ifndef SCRY_GL_UTILITY_H
#define SCRY_GL_UTILITY_H


#include <stdexcept>
#include <vector>
#include <gmtl/gmtl.h>
#include "OpenGL.h"
#include "Utility.h"


namespace scry {

    void checkOpenGLErrors();

    inline void glSetEnabled(GLenum cap, bool enabled) {
        (enabled ? glEnable : glDisable)(cap);
    }


    /**
     * GLTypeConstant maps Type to the GLenum for that type: float ->
     * GL_FLOAT, etc.
     */
    template<typename Type>
    struct GLTypeConstant;


    /**
     * GLType is the opposite of GLTypeConstant.  It maps a GLenum to the
     * associated type.  GL_FLOAT -> float, etc.
     */
    template<GLenum TypeConstant>
    struct GLType;


#define SCRY_MAP_TYPE_CONSTANT(type, constant) \
    template<>                                 \
    struct GLTypeConstant<type> {              \
        enum { Result = constant };            \
    };                                         \
                                               \
    template<>                                 \
    struct GLType<constant> {                  \
        typedef type Result;                   \
    };


    SCRY_MAP_TYPE_CONSTANT(GLubyte,  GL_UNSIGNED_BYTE);
    SCRY_MAP_TYPE_CONSTANT(GLbyte,   GL_BYTE);
    SCRY_MAP_TYPE_CONSTANT(GLushort, GL_UNSIGNED_SHORT);
    SCRY_MAP_TYPE_CONSTANT(GLshort,  GL_SHORT);
    SCRY_MAP_TYPE_CONSTANT(GLuint,   GL_UNSIGNED_INT);
    SCRY_MAP_TYPE_CONSTANT(GLint,    GL_INT);
    SCRY_MAP_TYPE_CONSTANT(GLfloat,  GL_FLOAT);
    SCRY_MAP_TYPE_CONSTANT(GLdouble, GL_DOUBLE);


    inline size_t getTypeSize(GLenum typeConstant) {
        switch (typeConstant) {
            //case GL_BITMAP: ??
            case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
            case GL_BYTE:           return sizeof(GLbyte);
            case GL_UNSIGNED_SHORT: return sizeof(GLushort);
            case GL_SHORT:          return sizeof(GLshort);
            case GL_UNSIGNED_INT:   return sizeof(GLuint);
            case GL_INT:            return sizeof(GLint);
            case GL_FLOAT:          return sizeof(GLfloat);
            default: SCRY_ASSERT(false && "Invalid type"); return 0;
        }
    }

    inline size_t getElementCount(GLenum format) {
        switch (format) {
            case GL_COLOR_INDEX:     return 1;
            case GL_STENCIL_INDEX:   return 1;
            case GL_DEPTH_COMPONENT: return 1;
            case GL_RED:             return 1;
            case GL_GREEN:           return 1;
            case GL_BLUE:            return 1;
            case GL_ALPHA:           return 1;
            case GL_RGB:             return 3;
            case GL_BGR:             return 3;
            case GL_RGBA:            return 4;
            case GL_BGRA:            return 4;
            case GL_LUMINANCE:       return 1;
            case GL_LUMINANCE_ALPHA: return 2;
            default: SCRY_ASSERT(false && "Invalid format"); return 0;
        }
    }


    inline size_t getVertexCountPerBatch(
        GLenum batchSize,
        GLenum primitiveType
    ) {
        switch (primitiveType) {
            case GL_POINTS:         return batchSize * 1; 
            case GL_LINES:          return batchSize * 2;
            case GL_LINE_STRIP:     return batchSize + 1;
            case GL_LINE_LOOP:      return batchSize;
            case GL_TRIANGLES:      return batchSize * 3;
            case GL_TRIANGLE_STRIP: return batchSize + 2;
            case GL_TRIANGLE_FAN:   return batchSize + 2;
            case GL_QUADS:          return batchSize * 4;
            case GL_QUAD_STRIP:     return batchSize * 2 + 2;
            case GL_POLYGON:        return batchSize;
            default:                return 0;
        }
    }


}


#endif
