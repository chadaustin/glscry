#include "IndexedGeometryTest.h"
using namespace boost::python;


namespace scry {

    void IndexedGeometryTest::bind() {
        class_< IndexedGeometryTest, IndexedGeometryTestPtr,
                bases<GeometryTest>, boost::noncopyable >
            ("IndexedGeometryTest", no_init)
            .def(init<const char*, GeometryPtr>());

        implicitly_convertible<IndexedGeometryTestPtr, GeometryTestPtr>();
    }

    void IndexedGeometryTest::setup() {
        GeometryTest::setup();

        GeometryPtr geo = getGeometry();
        ArrayPtr v = geo->vertices;
        if (!v) {
            assert(false && "Need vertices to actually render indexed geometry.");
        }

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(v->getSize(), v->getTypeConstant(),
                        0, getVertices().data_ptr());

        // Initialize the indices.
        _indices.resize(getVertexCount());
        for (size_t i = 0; i < _indices.size(); ++i) {
            _indices[i] = i;
        }
        
        // Shuffle.
        for (size_t i = 0; i < _indices.size(); ++i) {
            size_t idx = rand() % (_indices.size() - i);
            std::swap(_indices[i], _indices[i + idx]);
        }
    }

    void IndexedGeometryTest::iterate(ResultSet& results) {
        GeometryPtr geo = getGeometry();
        glDrawElements(geo->getPrimitiveType(), getVertexCount(),
                       GL_UNSIGNED_INT, &_indices[0]);
            
        results[0] += getVertexCount();
        results[1] += getBatchSize();
        results[2] += 0;  /// @todo: calculate fill rate
    }

    void IndexedGeometryTest::teardown() {
        glDisableClientState(GL_VERTEX_ARRAY);
    }

}
