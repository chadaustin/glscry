#include "CompiledVertexArrayTest.h"
using namespace boost::python;


namespace scry {

    void CompiledVertexArrayTest::bind() {
        class_<CompiledVertexArrayTest, CompiledVertexArrayTestPtr,
            bases<GeometryTest>, boost::noncopyable>
            ("CompiledVertexArrayTest", no_init)
            .def(init<const char*, GeometryGeneratorPtr>());

        implicitly_convertible<CompiledVertexArrayTestPtr, GeometryTestPtr>();
    }

}
