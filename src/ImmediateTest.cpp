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
#include "ImmediateTest.h"
using namespace boost::python;


namespace scry {

    void ImmediateTest::bind() {
        class_<ImmediateTest, ImmediateTestPtr, bases<GeometryTest>,
            boost::noncopyable>("ImmediateTest", no_init)
            .def(init<const char*, GeometryPtr>());

        implicitly_convertible<ImmediateTestPtr, GeometryTestPtr>();
    }

    void ImmediateTest::setup() {
        GeometryTest::setup();

        GeometryPtr geometry = getGeometry();
        if (ArrayPtr i = geometry->indices) {
            if (i->getSize() != 1) {
                throw std::runtime_error("Indices array contains vectors, scalars expected.");
            }

            if (ArrayPtr v = geometry->vertices) {
                glEnableClientState(GL_VERTEX_ARRAY);
                glVertexPointer(v, getVertices().data_ptr());
            }

            if (ArrayPtr c = geometry->colors) {
                glEnableClientState(GL_COLOR_ARRAY);
                glColorPointer(c, getColors().data_ptr());
            }

            if (ArrayPtr n = geometry->normals) {
                glEnableClientState(GL_NORMAL_ARRAY);
                assert(n->getSize() == 3);
                glNormalPointer(n, getNormals().data_ptr());
            }

            if (ArrayPtr t = geometry->texcoords) {
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glTexCoordPointer(t, getTexCoords().data_ptr());
            }
        }
    }

    void ImmediateTest::iterate(ResultSet& results) {
        GeometryPtr geometry = getGeometry();
        if (geometry->indices) {
            BufferIterator i(getIndices());

            glBegin(geometry->getPrimitiveType());
            for (size_t j = 0; j < getVertexCountPerBatch(); ++j) {
                i.step();
            }
            glEnd();
        } else {
            BufferIterator v(getVertices());
            BufferIterator c(getColors());
            BufferIterator n(getNormals());
            BufferIterator t(getTexCoords());

            glBegin(geometry->getPrimitiveType());
            for (size_t i = 0; i < getVertexCountPerBatch(); ++i) {
                c.step();
                n.step();
                t.step();
                v.step(); // vertices go last.
            }
            glEnd();
        }        

        results[0] += getVertexCountPerBatch();
        results[1] += getBatchSize();
        results[2] += getScreenCoverage();
        results[3] += 1;
    }

    void ImmediateTest::teardown() {
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

}
