#include "VertexArrayTest.h"
using namespace boost::python;


namespace scry {

    void VertexArrayTest::bind() {
        class_<VertexArrayTest, VertexArrayTestPtr, bases<GeometryTest>,
            boost::noncopyable>("VertexArrayTest", no_init)
            .def(init<GeometryGeneratorPtr>());

        implicitly_convertible<VertexArrayTestPtr, GeometryTestPtr>();
    }

}
