#ifndef SCRY_COMPILED_VERTEX_ARRAY_TEST
#define SCRY_COMPILED_VERTEX_ARRAY_TEST


#include "GeometryTest.h"
#include "GLUtility.h"


namespace scry {

    class CompiledVertexArrayTest : public GeometryTest {
    protected:
        ~CompiledVertexArrayTest() { }

    public:
        static void bind();

        CompiledVertexArrayTest(const char* name, GeometryPtr geo)
        : GeometryTest(name, geo) {
        }

        bool supported() const {
            return GLEW_EXT_compiled_vertex_array != 0;
        }

        void setup();
        void iterate(ResultSet& results);
        void teardown();
    };
    SCRY_REF_PTR(CompiledVertexArrayTest);

}


#endif
