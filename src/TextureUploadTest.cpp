#include <boost/python.hpp>
#include "TextureUploadTest.h"
using namespace boost::python;


namespace scry {

    void TextureUploadTest::bind() {
        class_< TextureUploadTest, TextureUploadTestPtr, bases<Test>,
                boost::noncopyable >("TextureUploadTest", no_init)
                .def(init<const char*>())
                .def("setWidth", &TextureUploadTest::setWidth)
                .def("setHeight", &TextureUploadTest::setHeight)
                .def("setType", &TextureUploadTest::setType)
                ;

        implicitly_convertible<TextureUploadTestPtr, TestPtr>();
    }

}
