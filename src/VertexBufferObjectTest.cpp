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
            _buffers.push_back(createVertexBuffer(getVertices()));

            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(v->getSize(), v->getTypeConstant(), 0, 0);
        }

        if (ArrayPtr c = geometry->colors) {
            _buffers.push_back(createVertexBuffer(getColors()));

            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(c->getSize(), c->getTypeConstant(), 0, 0);
        }

        if (ArrayPtr n = geometry->normals) {
            _buffers.push_back(createVertexBuffer(getNormals()));

            glEnableClientState(GL_NORMAL_ARRAY);
            assert(n->getSize() == 3);
            glNormalPointer(n->getTypeConstant(), 0, 0);
        }

        if (ArrayPtr t = geometry->texcoords) {
            _buffers.push_back(createVertexBuffer(getTexCoords()));

            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(t->getSize(), t->getTypeConstant(), 0, 0);
        }
    }

    void VertexBufferObjectTest::iterate(ResultSet& results) {
        GeometryPtr geo = getGeometry();

        // In indexing support, use glDrawRangeElements or glDrawElements.

        glDrawArrays(geo->getPrimitiveType(), 0, getVertexCountPerBatch());
        results[0] += getVertexCountPerBatch();
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

    GLuint VertexBufferObjectTest::createVertexBuffer(const Buffer& buffer) {
        GLuint handle;
        glGenBuffersARB(1, &handle);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, handle);
        glBufferDataARB(
            GL_ARRAY_BUFFER_ARB,
            buffer.data.size(),
            buffer.data_ptr(),
            GL_STATIC_DRAW_ARB /* This should be settable. */);
        return handle;
    }

}
