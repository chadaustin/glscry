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
#ifndef SCRY_DISPLAY_LIST_TEST_H
#define SCRY_DISPLAY_LIST_TEST_H


#include "GeometryTest.h"
#include "GLUtility.h"


namespace scry {

    class DisplayListTest : public GeometryTest {
    protected:
        ~DisplayListTest() { }

    public:
        static void bind();

        DisplayListTest(const char* name, GeometryPtr geo)
        : GeometryTest(name, geo) {
        }

        void setup();
        void iterate(ResultSet& results);
        void teardown();

    private:
        GLuint _list;
    };
    SCRY_REF_PTR(DisplayListTest);

}


#endif
