#include "VertexArrayTest.h"
using namespace boost::python;


namespace scry {

    void VertexArrayTest::bind() {
        class_<VertexArrayTest, VertexArrayTestPtr, bases<GeometryTest>,
            boost::noncopyable>("VertexArrayTest", no_init)
            .def(init<const char*, GeometryPtr>());

        implicitly_convertible<VertexArrayTestPtr, GeometryTestPtr>();
    }

}
