#ifndef SCRY_IMMEDIATE_TEST_H
#define SCRY_IMMEDIATE_TEST_H


#include "GeometryTest.h"
#include "GLUtility.h"


SCRY_BEGIN_NAMESPACE


class ImmediateTest : public GeometryTest {
protected:
    ~ImmediateTest() { }

public:
    static void bind();

    ImmediateTest(const char* name, GeometryPtr geo)
    : GeometryTest(name, geo) {
    }

    const char* name() const {
        return "Immediate";
    }

    void iterate(ResultSet& results) {
/*
        GeometryPtr geometry = getGeometry();

        _vertexCount = 0;

        void (GLAPI * glVertexd) = 0;

        if (ArrayPtr v = geometry->vertices) {
            glEnableClientState(GL_VERTEX_ARRAY);

            _vertexBuffer.resize(getVertexCount() * v->getSize() *
                                 v->getTypeSize());
            v->build(&_vertexBuffer[0], getVertexCount());
           
            glVertexPointer(v->getSize(), v->getTypeConstant(),
                            0, &_vertexBuffer[0]);

            _vertexCount = getVertexCount();
        }


        glBegin(geometry->getPrimitiveType());
        for (size_t i = 0; i < _vertexCount; ++i) {
            if (glVertexd) {
                glVertexd(data);
            }
        }
        glEnd();
        
        results[0] += _vertexCount;
/*
        const std::vector<Triangle>& buffer = getTriangleBuffer();

        glBegin(GL_TRIANGLES);
        for (size_t i = 0; i < buffer.size(); ++i) {
            glVertex(buffer[i].v1);
            glVertex(buffer[i].v2);
            glVertex(buffer[i].v3);
        }
        glEnd();
*/
    }
};
SCRY_REF_PTR(ImmediateTest);


SCRY_END_NAMESPACE


#endif
