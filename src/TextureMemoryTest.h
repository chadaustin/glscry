#ifndef SCRY_TEXTURE_MEMORY_TEST_H
#define SCRY_TEXTURE_MEMORY_TEST_H


#include <vector>
#include "OpenGL.h"
#include "Test.h"


namespace scry {

    class TextureMemoryTest : public Test {
    protected:
        ~TextureMemoryTest() { }

    public:
        SCRY_BEGIN_RESULT_DESCS()
            SCRY_RESULT_DESC("VertexRate", "vertex/s")
            SCRY_RESULT_DESC("PrimitiveRate", "tri/s")
        SCRY_END_RESULT_DESCS()

        static void bind();

        TextureMemoryTest(const char* name)
        : Test(name) {
        }

        const char* name() const {
            return "TextureMemoryTest";
        }

        size_t getTextureCount() const {
            return _textureCount;
        }
        void setTextureCount(size_t textureCount) {
            _textureCount = textureCount;
        }

        void setup();
        void iterate(ResultSet& results);
        void teardown();

    private:
        Inited<size_t, 512> _width;
        Inited<size_t, 512> _height;
        Inited<size_t, 1> _textureCount;
        std::vector<GLuint> _textures;

        Zeroed<size_t> _currentTexture;
    };
    SCRY_REF_PTR(TextureMemoryTest);

}


#endif
