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

    VertexArrayTest(const char* name, GeometryGeneratorPtr gen)
    : GeometryTest(name, gen) {
    }

    const char* name() const {
        return "Vertex Array";
    }

    void setup() {
        const std::vector<Triangle>& buffer = getTriangleBuffer();
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(buffer);
    }

    void iterate(ResultSet& results) {
        const std::vector<Triangle>& buffer = getTriangleBuffer();
        glDrawArrays(GL_TRIANGLES, 0, buffer.size() * 3);
        results[0] += buffer.size();
    }

    void teardown() {
        glDisableClientState(GL_VERTEX_ARRAY);
    }
};
SCRY_REF_PTR(VertexArrayTest);

SCRY_END_NAMESPACE


#endif
