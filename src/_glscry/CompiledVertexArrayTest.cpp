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
#include "CompiledVertexArrayTest.h"
using namespace boost::python;


namespace scry {

    void CompiledVertexArrayTest::bind() {
        class_<CompiledVertexArrayTest, CompiledVertexArrayTestPtr,
            bases<GeometryTest>, boost::noncopyable>
            ("CompiledVertexArrayTest", no_init)
            .def(init<const char*, GeometryPtr>());

        implicitly_convertible<CompiledVertexArrayTestPtr, GeometryTestPtr>();
    }

    void CompiledVertexArrayTest::setup() {
        GeometryTest::setup();

        enableArrays();
        glLockArraysEXT(0, getVertexArraySize());
    }

    void CompiledVertexArrayTest::iterate(ResultValues& results) {
        GeometryPtr geometry = getGeometry();
        if (ArrayPtr i = geometry->indices) {
            glDrawElements(geometry->getPrimitiveType(),
                           getVertexCountPerBatch(),
                           i->getTypeConstant(),
                           getIndices().data_ptr());
        } else {
            glDrawArrays(geometry->getPrimitiveType(),
                         0,
                         getVertexCountPerBatch());
        }
        results[0] += getVertexCountPerBatch();
        results[1] += getBatchSize();
        results[2] += getScreenCoverage();
        results[3] += 1;
    }

    void CompiledVertexArrayTest::teardown() {
        glUnlockArraysEXT();
        disableArrays();
    }
}
