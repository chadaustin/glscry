#ifndef SCRY_GL_UTILITY_H
#define SCRY_GL_UTILITY_H


#include <vector>
#include <gmtl/gmtl.h>
#include "Base.h"


SCRY_BEGIN_NAMESPACE

void glVertex(const gmtl::Vec3f& v) {
    glVertex3f(v[0], v[1], v[2]);
}


template<typename T>
void glVertexPointer(const std::vector<T>& array) {
    glVertexPointer(T::Size, T::TypeConstant, 0, &array[0]);
}

SCRY_END_NAMESPACE


#endif
