#ifndef SCRY_VERTEX_ARRAY_TEST
#define SCRY_VERTEX_ARRAY_TEST


#include "GeometryTest.h"
#include "GLUtility.h"


SCRY_BEGIN_NAMESPACE

class VertexArrayTest : public GeometryTest {
protected:
    ~VertexArrayTest() { }

public:
    static void bind();

    VertexArrayTest(const char* name, GeometryPtr geo)
    : GeometryTest(name, geo) {
    }

    const char* name() const {
        return "Vertex Array";
    }

    void setup() {
        GeometryPtr geometry = getGeometry();

        _vertexCount = 0;

        if (ArrayPtr v = geometry->vertices) {
            glEnableClientState(GL_VERTEX_ARRAY);

            _vertexBuffer.resize(getVertexCount() * v->getSize() *
                                 v->getTypeSize());
            v->build(&_vertexBuffer[0], getVertexCount());
           
            glVertexPointer(v->getSize(), v->getTypeConstant(),
                            0, &_vertexBuffer[0]);

            _vertexCount = getVertexCount();
        }
    }

    void iterate(ResultSet& results) {
        glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
        results[0] += _vertexCount;
    }

    void teardown() {
        glDisableClientState(GL_VERTEX_ARRAY);
    }

private:
    Zeroed<size_t> _vertexCount;
    std::vector<GLubyte> _vertexBuffer;
};
SCRY_REF_PTR(VertexArrayTest);

SCRY_END_NAMESPACE


#endif
