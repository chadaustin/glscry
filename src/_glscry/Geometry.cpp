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

        class_<ArrayPtrList>("ArrayList")
            .def(vector_indexing_suite<ArrayPtrList>())
            ;

        class_<Geometry, GeometryPtr, boost::noncopyable>
            ("Geometry", no_init)
            .def(init<GLenum>())
            .def_readwrite("indices",   &Geometry::indices)
            .def_readwrite("vertices",  &Geometry::vertices)
            .def_readwrite("colors",    &Geometry::colors)
            .def_readwrite("normals",   &Geometry::normals)
            .def_readwrite("texcoords", &Geometry::texcoords)
            ;
    }

    Geometry::Geometry(GLenum primitiveType) {
        _primitiveType = primitiveType;

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
