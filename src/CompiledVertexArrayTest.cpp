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

        glLockArraysEXT(0, getVertexArraySize());
    }

    void CompiledVertexArrayTest::iterate(ResultSet& results) {
        GeometryPtr geometry = getGeometry();
        glDrawArrays(geometry->getPrimitiveType(), 0, getVertexCountPerBatch());
        results[0] += getVertexCountPerBatch();
        results[1] += getBatchSize();
        results[2] += getScreenCoverage();
    }

    void CompiledVertexArrayTest::teardown() {
        glUnlockArraysEXT();
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
}
