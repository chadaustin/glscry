#include "CopyPixelTest.h"
using namespace boost::python;


namespace scry {

    void CopyPixelTest::bind() {
        class_< CopyPixelTest, CopyPixelTestPtr, bases<PixelTransferTest>,
                boost::noncopyable >("CopyPixelTest", no_init)
                    .def(init<const char*>());

        implicitly_convertible<CopyPixelTestPtr, PixelTransferTestPtr>();
    }

}
