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
#ifndef SCRY_COPY_PIXEL_TEST_H
#define SCRY_COPY_PIXEL_TEST_H


#include "OpenGL.h"
#include "PixelTransferTest.h"


namespace scry {

    class CopyPixelTest : public PixelTransferTest {
    protected:
        ~CopyPixelTest() { }

    public:
        static void bind();

        CopyPixelTest(const char* name)
        : PixelTransferTest(name) {
        }

        void setCopyType(GLenum copyType) { _copyType = copyType; }
        GLenum getCopyType() const        { return _copyType; }

        void iterate(ResultValues& results) {
            glCopyPixels(0, 0, getWidth(), getHeight(), getCopyType());
            results[0] += getWidth() * getHeight();
        }

    private:
        Inited<GLenum, GL_COLOR> _copyType;
    };
    SCRY_REF_PTR(CopyPixelTest);

}


#endif
