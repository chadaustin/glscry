#include "PixelTransferTest.h"
using namespace boost::python;


namespace scry {

    void PixelTransferTest::bind() {
        typedef PixelTransferTest C;
        class_<PixelTransferTest, PixelTransferTestPtr, bases<Test>,
               boost::noncopyable>("PixelTransferTest", no_init)
            .add_property("width",  &C::getWidth,  &C::setWidth)
            .add_property("height", &C::getHeight, &C::setHeight)
            .add_property("format", &C::getFormat, &C::setFormat)
            .add_property("type",   &C::getType,   &C::setType)
            ;

        implicitly_convertible<PixelTransferTestPtr, TestPtr>();
    }

}
