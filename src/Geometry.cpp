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
