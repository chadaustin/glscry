#include "DisplayListTest.h"
using namespace boost::python;


namespace scry {

    void DisplayListTest::bind() {
        class_<DisplayListTest, DisplayListTestPtr, bases<GeometryTest>,
            boost::noncopyable>("DisplayListTest", no_init)
            .def(init<const char*, GeometryPtr>());

        implicitly_convertible<DisplayListTestPtr, GeometryTestPtr>();
    }

}
