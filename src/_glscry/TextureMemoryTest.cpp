/* [Begin Copyright Header]
 *
 * GLScry - OpenGL Performance Analysis Tool
 * Copyright (C) 2004-2005  Iowa State University
 * 
 * This software is licensed under the terms of the GNU Lesser Public
 * License, version 2.1, as published by the Free Software Foundation.
 * See the file COPYRIGHT.txt for details.
 * 
 * Authors:
 *   Chad Austin <aegisk@iastate.edu>
 *   Dirk Reiners <dreiners@iastate.edu>
 *
 * [End Copyright Header] */
#include "TextureMemoryTest.h"
using namespace boost::python;


namespace scry {

    void TextureMemoryTest::bind() {
        typedef TextureMemoryTest C;
        class_<C, TextureMemoryTestPtr, bases<Test>,
               boost::noncopyable>("TextureMemoryTest", no_init)
            .def(init<const char*>())
            .add_property("textureCount",
                          &C::getTextureCount, &C::setTextureCount)
            ;

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
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D, 0, 4, _width, _height, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, &buffer[0]);
        }

        _currentTexture = 0;
    }

    void TextureMemoryTest::iterate(ResultValues& results) {
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

        results[0] += batchSize * 4;
        results[1] += batchSize;
    }

    void TextureMemoryTest::teardown() {
        glBindTexture(GL_TEXTURE_2D, 0);

        glDeleteTextures(_textureCount, &_textures[0]);
        _textures.clear();

        glDisable(GL_TEXTURE_2D);
    }

}
