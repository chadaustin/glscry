#ifndef SCRY_GL_UTILITY_H
#define SCRY_GL_UTILITY_H


#include <stdexcept>
#include <vector>
#include <gmtl/gmtl.h>
#include "Base.h"


SCRY_BEGIN_NAMESPACE


template<typename Type>
struct GLTypeConstant;

template<>
struct GLTypeConstant<float> {
    enum { Result = GL_FLOAT };
};

template<>
struct GLTypeConstant<double> {
    enum { Result = GL_DOUBLE };
};


template<GLenum TypeConstant>
struct GLType;

template<>
struct GLType<GL_FLOAT> {
    typedef float Result;
};

template<>
struct GLType<GL_DOUBLE> {
    typedef double Result;
};


template<size_t size, typename T>
const void* glVertex(const void* data);

#define SCRY_DEFINE_GL_VERTEX(wart, size, type)                        \
    template<>                                                         \
    inline const void* glVertex<size, type>(const void* data) {        \
        const type* v = static_cast<const type*>(data);                \
        glVertex##wart##v(v);                                          \
        return v + size;                                               \
    }

SCRY_DEFINE_GL_VERTEX(2f, 2, float);
SCRY_DEFINE_GL_VERTEX(3f, 3, float);
SCRY_DEFINE_GL_VERTEX(4f, 4, float);

SCRY_DEFINE_GL_VERTEX(2d, 2, double);
SCRY_DEFINE_GL_VERTEX(3d, 3, double);
SCRY_DEFINE_GL_VERTEX(4d, 4, double);


typedef const void* (*VertexPump)(const void* data);

inline VertexPump getVertexPump(GLenum type, size_t size) {
    switch (type) {
        case GL_FLOAT:
            switch (size) {
                case 2:  return glVertex<2, float>;
                case 3:  return glVertex<3, float>;
                case 4:  return glVertex<4, float>;
                default: throw std::runtime_error("Illegal Size");
            }
        case GL_DOUBLE:
            switch (size) {
                case 2:  return glVertex<2, double>;
                case 3:  return glVertex<3, double>;
                case 4:  return glVertex<4, double>;
                default: throw std::runtime_error("Illegal Size");
            }
        default:
            throw std::runtime_error("Unknown Type Constant");
    }
}


SCRY_END_NAMESPACE


#endif
