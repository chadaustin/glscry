#ifndef SCRY_TEXTURE_UPLOAD_TEST_H
#define SCRY_TEXTURE_UPLOAD_TEST_H


#include "Base.h"
#include "Test.h"


SCRY_BEGIN_NAMESPACE

class TextureUploadTest : public Test {
protected:
    ~TextureUploadTest() { }

public:
    static void bind();

    int getWidth() const       { return _width;  }
    void setWidth(int width)   { _width = width; }

    int getHeight() const      { return _height;   }
    void setHeight(int height) { _height = height; }

    int getType() const    { return _type; }
    void setType(int type) { _type = type; }

    const char* name() const {
        return "TextureUploadTest";
    }

    bool supported() const {
        return true;
    }

    SCRY_BEGIN_RESULT_DESCS()
      SCRY_RESULT_DESC("PixelRate", "pixels/sec")
      SCRY_RESULT_DESC("ByteRate",  "bytes/sec")
    SCRY_END_RESULT_DESCS()

    void setup() {
        glGenTextures(1, &_texture);
    }

    void iterate(ResultSet& results) {
        // Should add a way to test 1D and 3D textures.
        glBindTexture(GL_TEXTURE_2D, _texture);

        _buffer.resize(_width * _height * 4 * getTypeSize());

        // This call really needs to be customizable.
        glTexImage2D(GL_TEXTURE_2D, 0, 4, _width, _height, 0, GL_RGBA,
                     _type, &_buffer[0]);

        results[0] += _width * _height;
        results[1] += _buffer.size();
    }

    void teardown() {
        glDeleteTextures(1, &_texture);
    }

private:
    int getTypeSize() const {
        switch (_type.get()) {
            case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
            case GL_BYTE:           return sizeof(GLbyte);
//            case GL_BITMAP: ??
            case GL_UNSIGNED_SHORT: return sizeof(GLushort);
            case GL_SHORT:          return sizeof(GLshort);
            case GL_UNSIGNED_INT:   return sizeof(GLuint);
            case GL_INT:            return sizeof(GLint);
            case GL_FLOAT:          return sizeof(GLfloat);
            default: SCRY_ASSERT(false && "Invalid type"); return 0;
        }
    }

    Inited<int, 256>              _width;
    Inited<int, 256>              _height;
    //Inited<int, GL_RGBA>          _format;
    Inited<int, GL_UNSIGNED_BYTE> _type;

    GLuint _texture;
    // This might need to be aligned in some way.  Keep an eye out.
    std::vector<unsigned char> _buffer;
};
SCRY_REF_PTR(TextureUploadTest);


SCRY_END_NAMESPACE


#endif
