#ifndef SCRY_VERTEX_ARRAY_TEST
#define SCRY_VERTEX_ARRAY_TEST


#include "GeometryTest.h"
#include "GLUtility.h"


namespace scry {

    class VertexArrayTest : public GeometryTest {
    protected:
        ~VertexArrayTest() { }

    public:
        static void bind();

        VertexArrayTest(const char* name, GeometryPtr geo)
        : GeometryTest(name, geo) {
        }

        void setup();
        void iterate(ResultSet& results);
        void teardown();
    };
    SCRY_REF_PTR(VertexArrayTest);

}


#endif
