#ifndef SCRY_INDEXED_GEOMETRY_TEST_H
#define SCRY_INDEXED_GEOMETRY_TEST_H


#include "GeometryTest.h"


SCRY_BEGIN_NAMESPACE

class IndexedGeometryTest : public GeometryTest {
public:
    static const size_t triangleCount = 2048;

    IndexedGeometryTest(const GeometryGenerator* gen)
        : GeometryTest(gen)
    {
    }

    const char* name() const {
        return "IndexedGeometryTest";
    }

    bool supported() const {
        return true;
    }

    void setup() {
        const std::vector<Triangle>& buffer = getTriangleBuffer();
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(buffer);

        // Initialize the indices.
        _indices.resize(triangleCount * 3);
        for (size_t i = 0; i < triangleCount; ++i) {
            _indices[i] = rand() % (buffer.size() * 3);
        }
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

SCRY_END_NAMESPACE


#endif
