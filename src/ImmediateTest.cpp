#include "ImmediateTest.h"
using namespace boost::python;


namespace scry {

    void ImmediateTest::bind() {
        class_<ImmediateTest, ImmediateTestPtr, bases<GeometryTest>,
            boost::noncopyable>("ImmediateTest", no_init)
            .def(init<const char*, GeometryPtr>());

        implicitly_convertible<ImmediateTestPtr, GeometryTestPtr>();
    }

}
