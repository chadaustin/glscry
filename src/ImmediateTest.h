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

    void setup() {
        _vertexCount = getVertexCount();

        GeometryPtr geometry = getGeometry();

        if (ArrayPtr v = geometry->vertices) {
            _vertexBuffer.resize(_vertexCount * v->getSize() *
                                 v->getTypeSize());
            v->build(&_vertexBuffer[0], _vertexCount);

            _vertexPump = getVertexPump(v->getTypeConstant(), v->getSize());
        }
    }

    void iterate(ResultSet& results) {
        GeometryPtr geometry = getGeometry();

        const void* data = &_vertexBuffer[0];

        glBegin(geometry->getPrimitiveType());
        for (size_t i = 0; i < _vertexCount; ++i) {
            if (_vertexPump) {
                data = _vertexPump(data);
            }
        }
        glEnd();
        
        results[0] += _vertexCount;
    }

private:
    size_t _vertexCount;
    std::vector<GLubyte> _vertexBuffer;
    Zeroed<VertexPump> _vertexPump;
};
SCRY_REF_PTR(ImmediateTest);

SCRY_END_NAMESPACE

#endif
