#ifndef TRIAGARA_VERTEX_ARRAY_TEST
#define TRIAGARA_VERTEX_ARRAY_TEST


#include "GeometryTest.h"


TRIAGARA_BEGIN_NAMESPACE

class VertexArrayTest : public GeometryTest {
public:
    VertexArrayTest(const GeometryGenerator* gen)
        : GeometryTest(gen)
    {
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

TRIAGARA_END_NAMESPACE


#endif
