#include "IndexedGeometryTest.h"
using namespace boost::python;


namespace scry {

    void IndexedGeometryTest::bind() {
        class_< IndexedGeometryTest, IndexedGeometryTestPtr,
                bases<GeometryTest>, boost::noncopyable >
            ("IndexedGeometryTest", no_init)
            .def(init<GeometryGeneratorPtr>());

        implicitly_convertible<IndexedGeometryTestPtr, GeometryTestPtr>();
    }

}
