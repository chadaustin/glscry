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
#include "VertexArrayTest.h"
using namespace boost::python;


namespace scry {

    void VertexArrayTest::bind() {
        typedef VertexArrayTest C;
        typedef VertexArrayTestPtr CPtr;
        class_<C, CPtr, bases<GeometryTest>, boost::noncopyable>
            ("VertexArrayTest", no_init)
            .def(init<const char*, GeometryPtr>())
            .def_readwrite("compiled", &C::compiled)
            ;

        implicitly_convertible<CPtr, GeometryTestPtr>();
    }

    void VertexArrayTest::setup() {
        GeometryTest::setup();

        enableArrays();
        if (compiled) {
            glLockArraysEXT(0, getVertexArraySize(getGeometry()));
        }
    }

    void VertexArrayTest::iterate(ResultValues& results) {
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
        results[4] += getVertexCountPerBatch() * getVertexDataSize();
    }

    void VertexArrayTest::teardown() {
        if (compiled) {
            glUnlockArraysEXT();
        }
        disableArrays();
    }

}
