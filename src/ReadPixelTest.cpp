#include "ReadPixelTest.h"
using namespace boost::python;


namespace scry {

    void ReadPixelTest::bind() {
        class_< ReadPixelTest, ReadPixelTestPtr, bases<PixelTransferTest>,
                boost::noncopyable >("ReadPixelTest", no_init)
                    .def(init<>());

        implicitly_convertible<ReadPixelTestPtr, PixelTransferTestPtr>();
    }

}
