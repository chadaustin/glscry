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
        class_<VertexArrayTest, VertexArrayTestPtr, bases<GeometryTest>,
            boost::noncopyable>("VertexArrayTest", no_init)
            .def(init<const char*, GeometryPtr>());

        implicitly_convertible<VertexArrayTestPtr, GeometryTestPtr>();
    }

    void VertexArrayTest::setup() {
        GeometryTest::setup();

        GeometryPtr geometry = getGeometry();

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
            glNormalPointer(n, getNormals().data_ptr());
        }

        if (ArrayPtr t = geometry->texcoords) {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(t, getTexCoords().data_ptr());
        }
    }

    void VertexArrayTest::iterate(ResultSet& results) {
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

    void VertexArrayTest::teardown() {
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

}
