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
#ifndef SCRY_READ_PIXEL_TEST_H
#define SCRY_READ_PIXEL_TEST_H


#include "OpenGL.h"
#include "PixelTransferTest.h"


namespace scry {

    class ReadPixelTest : public PixelTransferTest {
    protected:
        ~ReadPixelTest() { }

    public:
        static void bind();

        ReadPixelTest(const char* name)
        : PixelTransferTest(name) {
        }

        void setup() {
            _buffer.resize(getWidth() * getHeight() *
                           getElementCount() * getTypeSize());
        }

        void iterate(ResultSet& results) {
            glReadPixels(0, 0, getWidth(), getHeight(),
                         getFormat(), getType(), &_buffer[0]);
            results[0] += getWidth() * getHeight();
            results[1] += getWidth() * getHeight() *
                          getElementCount() * getTypeSize();
        }

    private:
        std::vector<GLubyte> _buffer;
    };
    SCRY_REF_PTR(ReadPixelTest);

}


#endif
