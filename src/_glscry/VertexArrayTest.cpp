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
            glLockArraysEXT(0, getVertexArraySize());
        }
    }

    void VertexArrayTest::iterate(ResultValues& results) {
        GeometryPtr geometry = getGeometry();
        const PrimitiveBatchList& batches = geometry->batches;

        if (ArrayPtr i = geometry->indices) {
            size_t drawn = 0;
            for (size_t b = 0; b < batches.size(); ++b) {
                glDrawElements(batches[b].primitiveType,
                               batches[b].getVertexCount(),
                               i->getTypeConstant(),
                               getIndices().offset(drawn));
                drawn += batches[b].getVertexCount();
            }
        } else {
            size_t drawn = 0;
            for (size_t b = 0; b < batches.size(); ++b) {
                glDrawArrays(batches[b].primitiveType,
                             drawn,
                             batches[b].getVertexCount());
                drawn += batches[b].getVertexCount();
            }
        }

        results[0] += getVertexCountPerIteration();
        results[1] += getPrimitiveCountPerIteration();
        results[2] += getScreenCoverage();
        results[3] += geometry->batches.size();
        results[4] += getVertexCountPerIteration() * getVertexDataSize();
    }

    void VertexArrayTest::teardown() {
        if (compiled) {
            glUnlockArraysEXT();
        }
        disableArrays();
    }

}
