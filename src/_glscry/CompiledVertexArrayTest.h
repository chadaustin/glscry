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
#ifndef SCRY_COMPILED_VERTEX_ARRAY_TEST
#define SCRY_COMPILED_VERTEX_ARRAY_TEST


#include "GeometryTest.h"
#include "GLUtility.h"


namespace scry {

    class CompiledVertexArrayTest : public GeometryTest {
    protected:
        ~CompiledVertexArrayTest() { }

    public:
        static void bind();

        CompiledVertexArrayTest(const char* name, GeometryPtr geo)
        : GeometryTest(name, geo) {
        }

        bool isSupported() const {
            return GLEW_EXT_compiled_vertex_array != 0;
        }

        void setup();
        void iterate(ResultValues& results);
        void teardown();
    };
    SCRY_REF_PTR(CompiledVertexArrayTest);

}


#endif
