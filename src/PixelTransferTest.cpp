#include "PixelTransferTest.h"
using namespace boost::python;


namespace scry {

    void PixelTransferTest::bind() {
        class_<PixelTransferTest, PixelTransferTestPtr, bases<Test>,
               boost::noncopyable>("PixelTransferTest", no_init);

        implicitly_convertible<PixelTransferTestPtr, TestPtr>();
    }

}
