/* [Begin Copyright Header]
 *
 * GLScry - OpenGL Performance Analysis Tool
 * Copyright (C) 2004-2005  Iowa State University
 * 
 * This software is licensed under the terms of the GNU Lesser Public
 * License, version 2.1, as published by the Free Software Foundation.  
 * See the file COPYRIGHT.txt for details.
 * 
 * Authors:
 *   Chad Austin <aegisk@iastate.edu>
 *   Dirk Reiners <dreiners@iastate.edu>
 *
 * [End Copyright Header] */
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
