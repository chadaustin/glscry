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

    void setup();
    void iterate(ResultSet& results);
    void teardown();

private:
    Zeroed<size_t> _vertexCount;
    Zeroed<size_t> _screenCoverage;
    std::vector<GLubyte> _vertexBuffer;
};
SCRY_REF_PTR(VertexArrayTest);

SCRY_END_NAMESPACE


#endif
