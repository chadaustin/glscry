#ifndef SCRY_COMPILED_VERTEX_ARRAY_TEST
#define SCRY_COMPILED_VERTEX_ARRAY_TEST


#include "GeometryTest.h"
#include "GLUtility.h"


SCRY_BEGIN_NAMESPACE

class CompiledVertexArrayTest : public GeometryTest {
protected:
    ~CompiledVertexArrayTest() { }

public:
    static void bind();

    CompiledVertexArrayTest(const char* name, GeometryPtr geo)
    : GeometryTest(name, geo) {
    }

    const char* name() const {
        return "Compiled Vertex Array";
    }

    bool supported() const {
        return GLEW_EXT_compiled_vertex_array != 0;
    }

    void setup() {
#if 0
        const std::vector<Triangle>& buffer = getTriangleBuffer();

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(buffer);
        glLockArraysEXT(0, buffer.size());
#endif
    }

    void iterate(ResultSet& results) {
#if 0
        const std::vector<Triangle>& buffer = getTriangleBuffer();

        glDrawArrays(GL_TRIANGLES, 0, buffer.size() * 3);
        results[0] += buffer.size();
#endif
    }

    void teardown() {
#if 0
        glUnlockArraysEXT();
        glDisableClientState(GL_VERTEX_ARRAY);
#endif
    }
};
SCRY_REF_PTR(CompiledVertexArrayTest);

SCRY_END_NAMESPACE


#endif
