#ifndef SCRY_VERTEX_BUFFER_OBJECT_TEST
#define SCRY_VERTEX_BUFFER_OBJECT_TEST


#include "GeometryTest.h"
#include "GLUtility.h"


SCRY_BEGIN_NAMESPACE

class VertexBufferObjectTest : public GeometryTest {
protected:
    ~VertexBufferObjectTest() { }

public:
    static void bind();

    VertexBufferObjectTest(const char* name, GeometryPtr geo)
    : GeometryTest(name, geo) {
    }

    const char* name() const {
        return "Vertex Buffer Object";
    }

    bool supported() const {
        return GLEW_ARB_vertex_buffer_object != 0;
    }

    void setup() {
        _vertexCount = getVertexCount();

        GeometryPtr geometry = getGeometry();

        glGenBuffersARB(1, &_buffer);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, _buffer);


        if (ArrayPtr v = geometry->vertices) {
            glEnableClientState(GL_VERTEX_ARRAY);

            std::vector<GLubyte> vertexBuffer(
                _vertexCount * v->getSize() * v->getTypeSize());
            v->build(&vertexBuffer[0], _vertexCount);

            glBufferDataARB(
                GL_ARRAY_BUFFER_ARB,
                vertexBuffer.size(),
                &vertexBuffer[0],
                GL_STATIC_DRAW_ARB /* This should be settable. */);

            ::glVertexPointer(v->getSize(), v->getTypeConstant(), 0, NULL);
        }
    }

    void iterate(ResultSet& results) {
        GeometryPtr geo = getGeometry();
        glDrawArrays(geo->getPrimitiveType(), 0, _vertexCount);
        results[0] += _vertexCount;
    }

    void teardown() {
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

        glDeleteBuffersARB(1, &_buffer);
    }

private:
    size_t _vertexCount;
    GLuint _buffer;
};
SCRY_REF_PTR(VertexBufferObjectTest);


SCRY_END_NAMESPACE


#endif
