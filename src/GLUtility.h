#ifndef SCRY_GL_UTILITY_H
#define SCRY_GL_UTILITY_H


#include <stdexcept>
#include <vector>
#include <gmtl/gmtl.h>
#include "glew.h"


namespace scry {


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



    typedef const void* (*Pump)(const void* data);

    Pump getVertexPump(GLenum type, int size);
    Pump getColorPump(GLenum type, int size);
    Pump getNormalPump(GLenum type, int size);
    Pump getTexCoord(GLenum type, int size);

}


#endif
