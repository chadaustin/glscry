#include "TextureMemoryTest.h"
using namespace boost::python;


namespace scry {

    void TextureMemoryTest::bind() {
        class_<TextureMemoryTest, TextureMemoryTestPtr, bases<Test>,
               boost::noncopyable>("TextureMemoryTest", no_init)
            .def(init<>());

        implicitly_convertible<TextureMemoryTestPtr, TestPtr>();
    }

    void TextureMemoryTest::setup() {
        _textures.resize(_textureCount);
        glGenTextures(_textureCount, &_textures[0]);

        std::vector<unsigned char> buffer;

        glEnable(GL_TEXTURE_2D);

        // Create the textures.
        for (size_t i = 0; i < _textureCount; ++i) {
            buffer.resize(_width * _height * 4);

            // This call really needs to be customizable.
            glBindTexture(GL_TEXTURE_2D, _textures[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, 4, _width, _height, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, &buffer[0]);
        }

        _currentTexture = 0;
    }

    void TextureMemoryTest::iterate(ResultSet& results) {
        const size_t batchSize = 1024;

        for (size_t i = 0; i < batchSize; ++i) {
            glBindTexture(GL_TEXTURE_2D, _textures[_currentTexture]);
            _currentTexture = (_currentTexture + 1) % _textureCount;

            glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0); glVertex2f(0,  0);
            glTexCoord2f(0, 1); glVertex2f(0,  16);
            glTexCoord2f(1, 1); glVertex2f(16, 16);
            glTexCoord2f(1, 0); glVertex2f(16, 0);
            glEnd();
        }

        results[0] += batchSize * 2;
    }

    void TextureMemoryTest::teardown() {
        glBindTexture(GL_TEXTURE_2D, 0);

        glDeleteTextures(_textureCount, &_textures[0]);
        _textures.clear();

        glDisable(GL_TEXTURE_2D);
    }

}
