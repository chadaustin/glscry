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

        results[0] += getVertexCountPerIteration();
        results[1] += getPrimitiveCountPerIteration();
        results[2] += getScreenCoverage();
        results[3] += getBatchesPerIteration();
        results[4] += getVertexCountPerIteration() * getVertexDataSize();
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
            if (i->getVectorSize() != 1) {
                throw std::runtime_error("Indices array contains vectors, scalars expected.");
            }

            enableArrays();
        }
    }

    void ImmediateTest::doIterate() {
        GeometryPtr geometry = getGeometry();
        const PrimitiveBatchList& batches = geometry->batches;

        if (geometry->indices) {
            BufferIterator i(getIndices());

            for (size_t b = 0; b < batches.size(); ++b) {
                glBegin(batches[b].primitiveType);
                for (size_t j = 0; j < batches[b].getVertexCount(); ++j) {
                    i.step();
                }
                glEnd();
            }
        } else {
            BufferIteratorList bi;
            fillBufferIteratorList(bi);

            for (size_t b = 0; b < batches.size(); ++b) {
                glBegin(batches[b].primitiveType);
                for (size_t i = 0; i < batches[b].getVertexCount(); ++i) {
                    std::for_each(bi.begin(), bi.end(),
                                  std::mem_fun_ref(&BufferIterator::step));
                }
                glEnd();
            }
        }
    }

    void ImmediateTest::doTeardown() {
        disableArrays();
    }

}
