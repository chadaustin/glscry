#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "Geometry.h"
using namespace boost::python;


namespace scry {

    void Array::bind() {
        scope s = class_<Array, ArrayPtr, boost::noncopyable>
            ("Arrayf", no_init)
            .def(init<size_t>())
            .def_readwrite("initial", &Array::initial)
            .def_readwrite("repeat",  &Array::repeat)
            .def_readwrite("offset",  &Array::offset);

        class_<List>("List")
            .def(vector_indexing_suite<List>());
    }

    void Geometry::bind() {
        class_<Geometry, GeometryPtr, boost::noncopyable>
            ("Geometry", no_init)
            .def(init<GLenum>())
            .def_readwrite("vertices", &Geometry::vertices)
            .def_readwrite("colors",   &Geometry::colors)
            .def_readwrite("normals",  &Geometry::normals);

    }

    Geometry::Geometry(GLenum primitiveType) {
        _primitiveType = primitiveType;
    }

}
