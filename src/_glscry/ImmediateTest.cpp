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
#include <functional>
#include "ImmediateTest.h"
using namespace boost::python;


namespace scry {

    void ImmediateTest::bind() {
        typedef ImmediateTest C;
        typedef ImmediateTestPtr CPtr;
        class_<C, CPtr, bases<GeometryTest>, boost::noncopyable>
            ("ImmediateTest", no_init)
            .def(init<const char*, GeometryPtr>())
            .def_readwrite("useList", &C::useList)
            ;

        implicitly_convertible<CPtr, GeometryTestPtr>();
    }

    void ImmediateTest::setup() {
        GeometryTest::setup();

        doSetup();

        if (useList) {
            _list = glGenLists(1);
            glNewList(_list, GL_COMPILE);

            doIterate();

            glEndList();
        }
    }

    void ImmediateTest::iterate(ResultValues& results) {
        if (useList) {
            glCallList(_list);
        } else {
            doIterate();
        }

        results[0] += getVertexCountPerBatch();
        results[1] += getBatchSize();
        results[2] += getScreenCoverage();
        results[3] += 1;        
    }

    void ImmediateTest::teardown() {
        if (useList) {
            glDeleteLists(_list, 1);
        }

        doTeardown();
    }

    void ImmediateTest::doSetup() {
        GeometryPtr geometry = getGeometry();
        if (ArrayPtr i = geometry->indices) {
            if (i->getSize() != 1) {
                throw std::runtime_error("Indices array contains vectors, scalars expected.");
            }

            enableArrays();
        }
    }

    void ImmediateTest::doIterate() {
        GeometryPtr geometry = getGeometry();
        if (geometry->indices) {
            BufferIterator i(getIndices());

            glBegin(geometry->getPrimitiveType());
            for (size_t j = 0; j < getVertexCountPerBatch(); ++j) {
                i.step();
            }
            glEnd();
        } else {
            BufferIteratorList bi;
            fillBufferIteratorList(bi);

            glBegin(geometry->getPrimitiveType());
            for (size_t i = 0; i < getVertexCountPerBatch(); ++i) {
                std::for_each(bi.begin(), bi.end(),
                              std::mem_fun_ref(&BufferIterator::step));
            }
            glEnd();
        }
    }

    void ImmediateTest::doTeardown() {
        disableArrays();
    }

}
