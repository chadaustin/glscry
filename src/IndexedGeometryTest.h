#ifndef SCRY_INDEXED_GEOMETRY_TEST_H
#define SCRY_INDEXED_GEOMETRY_TEST_H


#include "GeometryTest.h"
#include "GLUtility.h"


SCRY_BEGIN_NAMESPACE

class IndexedGeometryTest : public GeometryTest {
protected:
    ~IndexedGeometryTest() { }

public:
    static void bind();

    static const size_t triangleCount = 2048;

    IndexedGeometryTest(const char* name, GeometryPtr geo)
    : GeometryTest(name, geo) {
    }

    const char* name() const {
        return "IndexedGeometryTest";
    }

    bool supported() const {
        return true;
    }

    void setup() {
#if 0
        const std::vector<Triangle>& buffer = getTriangleBuffer();
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(buffer);

        // Initialize the indices.
        _indices.resize(triangleCount * 3);
        for (size_t i = 0; i < triangleCount; ++i) {
            _indices[i] = rand() % (buffer.size() * 3);
        }
#endif
    }

    void iterate(ResultSet& results) {
        glDrawElements(GL_TRIANGLES, _indices.size(),
                       GL_UNSIGNED_INT, &_indices[0]);

        results[0] += triangleCount;
    }

    void teardown() {
        glDisableClientState(GL_VERTEX_ARRAY);
    }

private:
    Inited<int, 256> _arraySize;

    std::vector<GLuint> _indices;
};
SCRY_REF_PTR(IndexedGeometryTest);

SCRY_END_NAMESPACE


#endif
