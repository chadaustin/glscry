#include "GeometryGenerator.h"
using namespace boost::python;


namespace scry {

    void GeometryGenerator::bind() {
        class_<GeometryGenerator, GeometryGeneratorPtr, boost::noncopyable>
            ("GeometryGenerator", no_init);
    }

    void Zeroes::bind() {
        class_<Zeroes, ZeroesPtr, bases<GeometryGenerator>, boost::noncopyable>
            ("Zeroes", no_init)
            .def(init<>());

        implicitly_convertible<ZeroesPtr, GeometryGeneratorPtr>();
    }

    void SmallTriangles::bind() {
        class_<SmallTriangles, SmallTrianglesPtr, bases<GeometryGenerator>, boost::noncopyable>
            ("SmallTriangles", no_init)
            .def(init<>());

        implicitly_convertible<SmallTrianglesPtr, GeometryGeneratorPtr>();
    }

}
