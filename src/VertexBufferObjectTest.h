#ifndef SCRY_VERTEX_BUFFER_OBJECT_TEST
#define SCRY_VERTEX_BUFFER_OBJECT_TEST


#include "GeometryTest.h"
#include "GLUtility.h"


namespace scry {

    class VertexBufferObjectTest : public GeometryTest {
    protected:
        ~VertexBufferObjectTest() { }

    public:
        static void bind();

        VertexBufferObjectTest(const char* name, GeometryPtr geo)
        : GeometryTest(name, geo) {
        }

        void setBufferType(GLenum type) {
            _bufferType = type;
        }

        bool supported() const {
            return GLEW_ARB_vertex_buffer_object != 0;
        }

        void setup();
        void iterate(ResultSet& results);
        void teardown();

    private:
        GLuint createVBO(const Buffer& buffer,
                         GLenum target = GL_ARRAY_BUFFER_ARB);

        Inited<GLenum, GL_STATIC_DRAW_ARB> _bufferType;
        std::vector<GLuint> _buffers;
    };
    SCRY_REF_PTR(VertexBufferObjectTest);

}


#endif
