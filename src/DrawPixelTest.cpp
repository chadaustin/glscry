#include "DrawPixelTest.h"
using namespace boost::python;


namespace scry {

    void DrawPixelTest::bind() {
        class_< DrawPixelTest, DrawPixelTestPtr, bases<PixelTransferTest>,
                boost::noncopyable >("DrawPixelTest", no_init)
                    .def(init<>());

        implicitly_convertible<DrawPixelTestPtr, PixelTransferTestPtr>();
    }

}
