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
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "Array.h"
using namespace boost::python;


namespace scry {

    size_t ArrayInterface::getTypeSize() const {
        switch (getTypeConstant()) {
            case GL_BITMAP:         throw std::runtime_error("GL_BITMAP not supported.");
            case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
            case GL_BYTE:           return sizeof(GLbyte);
            case GL_UNSIGNED_SHORT: return sizeof(GLushort);
            case GL_SHORT:          return sizeof(GLshort);
            case GL_UNSIGNED_INT:   return sizeof(GLuint);
            case GL_INT:            return sizeof(GLint);
            case GL_FLOAT:          return sizeof(GLfloat);
            case GL_DOUBLE:         return sizeof(GLdouble);
            default:                throw std::runtime_error("Unknown type constant");
        }
    }


    template<typename T>
    void bindArray(const char* name) {
        typedef Array<T> ArrayType;
        typedef boost::intrusive_ptr<ArrayType> ArrayTypePtr;

        scope s = class_<ArrayType, ArrayTypePtr, bases<ArrayInterface>,
            boost::noncopyable>(name, no_init)
            .def(init<size_t>())
            .def_readwrite("initial", &ArrayType::initial)
            .def_readwrite("repeat",  &ArrayType::repeat)
            .def_readwrite("offset",  &ArrayType::offset)
            ;
        
        typedef typename ArrayType::List List;
        class_<List>("List")
            .def(vector_indexing_suite<List>())
            ;

        implicitly_convertible<ArrayTypePtr, ArrayPtr>();
    }

    void bindArrayTypes() {
        class_<ArrayInterface, ArrayPtr, boost::noncopyable>
            ("ArrayInterface", no_init);

        bindArray<GLubyte> ("Array_ub");
        bindArray<GLbyte>  ("Array_b");
        bindArray<GLushort>("Array_us");
        bindArray<GLshort> ("Array_s");
        bindArray<GLuint>  ("Array_ui");
        bindArray<GLint>   ("Array_i");
        bindArray<GLfloat> ("Array_f");
        bindArray<GLdouble>("Array_d");
    }

}
