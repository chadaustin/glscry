#include "VertexBufferObjectTest.h"
using namespace boost::python;


namespace scry {

    void VertexBufferObjectTest::bind() {
        class_<VertexBufferObjectTest, VertexBufferObjectTestPtr,
            bases<GeometryTest>, boost::noncopyable>
            ("VertexBufferObjectTest", no_init)
            .def(init<const char*, GeometryPtr>());

        implicitly_convertible<VertexBufferObjectTestPtr, GeometryTestPtr>();
    }

    void VertexBufferObjectTest::setup() {
        GeometryTest::setup();

        GeometryPtr geometry = getGeometry();
        if (ArrayPtr v = geometry->vertices) {
            GLuint buffer;
            glGenBuffersARB(1, &buffer);
            glBindBufferARB(GL_ARRAY_BUFFER_ARB, buffer);
            glBufferDataARB(
                GL_ARRAY_BUFFER_ARB,
                getVertices().data.size(),
                getVertices().data_ptr(),
                GL_STATIC_DRAW_ARB /* This should be settable. */);

            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(v->getSize(), v->getTypeConstant(), 0, 0);

            _buffers.push_back(buffer);
        }

        if (ArrayPtr c = geometry->colors) {
            GLuint buffer;
            glGenBuffersARB(1, &buffer);
            glBindBufferARB(GL_ARRAY_BUFFER_ARB, buffer);
            glBufferDataARB(
                GL_ARRAY_BUFFER_ARB,
                getColors().data.size(),
                getColors().data_ptr(),
                GL_STATIC_DRAW_ARB /* This should be settable. */);

            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(c->getSize(), c->getTypeConstant(), 0, 0);

            _buffers.push_back(buffer);
        }

        if (ArrayPtr n = geometry->normals) {
            GLuint buffer;
            glGenBuffersARB(1, &buffer);
            glBindBufferARB(GL_ARRAY_BUFFER_ARB, buffer);
            glBufferDataARB(
                GL_ARRAY_BUFFER_ARB,
                getNormals().data.size(),
                getNormals().data_ptr(),
                GL_STATIC_DRAW_ARB /* This should be settable. */);

            glEnableClientState(GL_NORMAL_ARRAY);
            assert(n->getSize() == 3);
            glNormalPointer(n->getTypeConstant(), 0, 0);

            _buffers.push_back(buffer);
        }

        if (ArrayPtr t = geometry->texcoords) {
            GLuint buffer;
            glGenBuffersARB(1, &buffer);
            glBindBufferARB(GL_ARRAY_BUFFER_ARB, buffer);
            glBufferDataARB(
                GL_ARRAY_BUFFER_ARB,
                getTexCoords().data.size(),
                getTexCoords().data_ptr(),
                GL_STATIC_DRAW_ARB /* This should be settable. */);

            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(t->getSize(), t->getTypeConstant(), 0, 0);

            _buffers.push_back(buffer);
        }
    }

    void VertexBufferObjectTest::iterate(ResultSet& results) {
        GeometryPtr geo = getGeometry();
        glDrawArrays(geo->getPrimitiveType(), 0, getVertexCount());
        results[0] += getVertexCount();
        results[1] += getBatchSize();
        results[2] += getScreenCoverage();
    }

    void VertexBufferObjectTest::teardown() {
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
        for (size_t i = 0; i < _buffers.size(); ++i) {
            glDeleteBuffersARB(1, &_buffers[i]);
        }
    }
}
