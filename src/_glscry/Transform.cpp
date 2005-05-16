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
