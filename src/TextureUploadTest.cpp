#include <boost/python.hpp>
#include "TextureUploadTest.h"
using namespace boost::python;


TRIAGARA_BEGIN_NAMESPACE


void TextureUploadTest::bind() {
    class_< TextureUploadTest, bases<Test> >("TextureUploadTest")
        .def("setWidth", &TextureUploadTest::setWidth)
        .def("setHeight", &TextureUploadTest::setHeight)
        .def("setType", &TextureUploadTest::setType);
}


TRIAGARA_END_NAMESPACE
