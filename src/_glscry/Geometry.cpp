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
#include "Geometry.h"
using namespace boost::python;


namespace scry {

    void Geometry::bind() {
        class_<PrimitiveBatch>("PrimitiveBatch", no_init)
            .def(init<GLenum, size_t>())
            ;

        class_<PrimitiveBatchList>("PrimitiveBatchList")
            .def(vector_indexing_suite<PrimitiveBatchList>())
            ;

        class_<ArrayPtrList>("ArrayList")
            .def(vector_indexing_suite<ArrayPtrList>())
            ;

        typedef Geometry C;
        class_<C, GeometryPtr, boost::noncopyable>
            ("Geometry", no_init)
            .def(init<>())
            .def_readwrite("batches",      &C::batches)
            .def_readwrite("indices",      &C::indices)
            .def_readwrite("vertices",     &C::vertices)
            .def_readwrite("colors",       &C::colors)
            .def_readwrite("normals",      &C::normals)
            .def_readwrite("texcoords",    &C::texcoords)
            ;
    }


    Geometry::Geometry() {
        if (GLEW_ARB_multitexture) {
            GLint textureCount;
            glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &textureCount);
            SCRY_ASSERT(textureCount >= 1);
            _maxTextureUnits = textureCount;
        } else {
            _maxTextureUnits = 1;
        }
        
        texcoords.resize(_maxTextureUnits);
    }


}
