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
