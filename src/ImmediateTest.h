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

    ImmediateTest(GeometryGeneratorPtr gen)
        : GeometryTest(gen)
    {
    }

    const char* name() const {
        return "Immediate";
    }

    void iterate(ResultSet& results) {
        const std::vector<Triangle>& buffer = getTriangleBuffer();

        glBegin(GL_TRIANGLES);
        for (size_t i = 0; i < buffer.size(); ++i) {
            glVertex(buffer[i].v1);
            glVertex(buffer[i].v2);
            glVertex(buffer[i].v3);
        }
        glEnd();

        results[0] += buffer.size();
    }
};
SCRY_REF_PTR(ImmediateTest);


SCRY_END_NAMESPACE


#endif
