#include "Geometry.h"
using namespace boost::python;


namespace scry {

    void Geometry::bind() {
        class_<Geometry, GeometryPtr, boost::noncopyable>
            ("Geometry", no_init)
            .def(init<GLenum>());
    }

    Geometry::Geometry(GLenum primitiveType) {
        _primitiveType = primitiveType;
    }

}
