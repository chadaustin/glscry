#ifndef SCRY_INDEXED_GEOMETRY_TEST_H
#define SCRY_INDEXED_GEOMETRY_TEST_H


#include "GeometryTest.h"
#include "GLUtility.h"


namespace scry {

    class IndexedGeometryTest : public GeometryTest {
    protected:
        ~IndexedGeometryTest() { }

    public:
        static void bind();

        IndexedGeometryTest(const char* name, GeometryPtr geo)
        : GeometryTest(name, geo) {
        }

        void setup();
        void iterate(ResultSet& results);
        void teardown();

    private:
        std::vector<GLuint> _indices;
    };
    SCRY_REF_PTR(IndexedGeometryTest);

}


#endif
