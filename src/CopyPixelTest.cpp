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
#include "CopyPixelTest.h"
using namespace boost::python;


namespace scry {

    void CopyPixelTest::bind() {
        class_< CopyPixelTest, CopyPixelTestPtr, bases<PixelTransferTest>,
                boost::noncopyable >("CopyPixelTest", no_init)
            .def(init<const char*>())
            .add_property("copyType", &CopyPixelTest::getCopyType,
                                      &CopyPixelTest::setCopyType)
            ;

        implicitly_convertible<CopyPixelTestPtr, PixelTransferTestPtr>();
    }

}
