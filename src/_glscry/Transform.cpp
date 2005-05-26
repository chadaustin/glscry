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
#include <boost/python.hpp>
#include "OpenGL.h"
#include "Transform.h"
using namespace boost::python;


namespace scry {

    void Transform::bind() {
        class_<Transform, TransformPtr, boost::noncopyable>
            ("Transform", no_init)
            ;

        class_<IdentityTransform, IdentityTransformPtr, bases<Transform>,
               boost::noncopyable>
            ("IdentityTransform", no_init)
            .def(init<>())
            ;
        implicitly_convertible<IdentityTransformPtr, TransformPtr>();

        class_<MatrixTransform, MatrixTransformPtr, bases<Transform>,
               boost::noncopyable>
            ("MatrixTransform", no_init)
            .def(init<const Matrix44f&>())
            ;
        implicitly_convertible<MatrixTransformPtr, TransformPtr>();
    }


    void IdentityTransform::apply() {
        glLoadIdentity();
    }


    void MatrixTransform::apply() {
        glLoadMatrixf(_matrix.getData());
    }

}
