#ifndef SCRY_DISPLAY_LIST_TEST_H
#define SCRY_DISPLAY_LIST_TEST_H


#include "GeometryTest.h"
#include "GLUtility.h"


SCRY_BEGIN_NAMESPACE

class DisplayListTest : public GeometryTest {
protected:
    ~DisplayListTest() { }

public:
    static void bind();

    DisplayListTest(const char* name, GeometryPtr geo)
    : GeometryTest(name, geo) {
    }

    const char* name() const {
        return "Display List";
    }

    void setup() {
        _vertexCount = getVertexCount();

        GeometryPtr geometry = getGeometry();

        std::vector<GLubyte> vertexBuffer;
        VertexPump vertexPump = 0;

        if (ArrayPtr v = geometry->vertices) {
            vertexBuffer.resize(_vertexCount * v->getSize() *
                                 v->getTypeSize());
            v->build(&vertexBuffer[0], _vertexCount);

            vertexPump = getVertexPump(v->getTypeConstant(), v->getSize());
        }


        _list = glGenLists(1);
        glNewList(_list, GL_COMPILE);

        const void* data = &vertexBuffer[0];
        glBegin(geometry->getPrimitiveType());
        for (size_t i = 0; i < _vertexCount; ++i) {
            if (vertexPump) {
                data = vertexPump(data);
            }
        }
        glEnd();

        glEndList();
    }

    void iterate(ResultSet& results) {
        glCallList(_list);
        results[0] += _vertexCount;
    }

    void teardown() {
        glDeleteLists(_list, 1);
    }

private:
    size_t _vertexCount;
    GLuint _list;
};
SCRY_REF_PTR(DisplayListTest);


SCRY_END_NAMESPACE


#endif
