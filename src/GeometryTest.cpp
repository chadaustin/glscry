#include "GeometryTest.h"
using namespace boost::python;


namespace scry {

    void GeometryTest::bind() {
        class_<GeometryTest, GeometryTestPtr, bases<Test>, boost::noncopyable>
            ("GeometryTest", no_init);

        implicitly_convertible<GeometryTestPtr, TestPtr>();
    }

}
