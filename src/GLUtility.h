#ifndef SCRY_GL_UTILITY_H
#define SCRY_GL_UTILITY_H


#include <stdexcept>
#include <vector>
#include <gmtl/gmtl.h>
#include "glew.h"
#include "Base.h"


SCRY_BEGIN_NAMESPACE


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



#if 0
inline Pump getColorPump(GLenum type, size_t size) {
#define SCRY_GET_COLOR_PUMP_SIZE_CASE(size, type)       \
    case size: return glColor<size, type>

#define SCRY_GET_COLOR_PUMP_TYPE_CASE(type)                     \
    case GLTypeConstant<type>::Result:                          \
        switch (size) {                                         \
            SCRY_GET_COLOR_PUMP_SIZE_CASE(2, type);             \
            SCRY_GET_COLOR_PUMP_SIZE_CASE(3, type);             \
            SCRY_GET_COLOR_PUMP_SIZE_CASE(4, type);             \
            default: throw std::runtime_error("Illegal Size");  \
        }

    switch (type) {
        SCRY_GET_COLOR_PUMP_TYPE_CASE(float);
        SCRY_GET_COLOR_PUMP_TYPE_CASE(double);
        default: throw std::runtime_error("Unknown Type Constant");
    }
}
#endif

SCRY_END_NAMESPACE


#endif
