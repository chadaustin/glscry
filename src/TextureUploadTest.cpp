#include <boost/python.hpp>
#include "TextureUploadTest.h"
using namespace boost::python;


SCRY_BEGIN_NAMESPACE


void TextureUploadTest::bind() {
    class_< TextureUploadTest, TextureUploadTestPtr, bases<Test>,
            boost::noncopyable >("TextureUploadTest", no_init)
        .def(init<>())
        .def("setWidth", &TextureUploadTest::setWidth)
        .def("setHeight", &TextureUploadTest::setHeight)
        .def("setType", &TextureUploadTest::setType);

    implicitly_convertible<TextureUploadTestPtr, TestPtr>();
}


SCRY_END_NAMESPACE
