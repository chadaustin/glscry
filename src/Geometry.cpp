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
#include "Geometry.h"
using namespace boost::python;


namespace scry {

    void Geometry::bind() {
        class_<Geometry, GeometryPtr, boost::noncopyable>
            ("Geometry", no_init)
            .def(init<GLenum>())
            .def_readwrite("vertices",  &Geometry::vertices)
            .def_readwrite("colors",    &Geometry::colors)
            .def_readwrite("normals",   &Geometry::normals)
            .def_readwrite("texcoords", &Geometry::texcoords)
            .def_readwrite("indices",   &Geometry::indices)
            ;
    }

    Geometry::Geometry(GLenum primitiveType) {
        _primitiveType = primitiveType;
    }

}
