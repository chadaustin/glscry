#ifndef SCRY_PIXEL_TRANSFER_TEST
#define SCRY_PIXEL_TRANSFER_TEST


#include "GLUtility.h"
#include "Test.h"


namespace scry {

    class PixelTransferTest : public Test {
    protected:
        ~PixelTransferTest() { }

    public:
        SCRY_BEGIN_RESULT_DESCS()
            SCRY_RESULT_DESC("PixelRate", "pixels/sec")
            SCRY_RESULT_DESC("ByteRate",  "bytes/sec")
        SCRY_END_RESULT_DESCS()

        static void bind();

        PixelTransferTest(const char* name)
        : Test(name) {
        }

        void setWidth(size_t width)   { _width  = width;  }
        size_t getWidth() const       { return _width; }

        void setHeight(size_t height) { _height = height; }
        size_t getHeight() const      { return _height; }

        void setFormat(GLenum format) { _format = format; }
        GLenum getFormat() const      { return _format; }

        void setType(GLenum type)     { _type = type; }
        GLenum getType() const        { return _type; }

    protected:
        size_t getTypeSize() const {
            return scry::getTypeSize(_type);
        }
        
        size_t getElementCount() const {
            return scry::getElementCount(_format);
        }

    private:
        Inited<size_t, 512>              _width;
        Inited<size_t, 512>              _height;
        Inited<GLenum, GL_RGBA>          _format;
        Inited<GLenum, GL_UNSIGNED_BYTE> _type;
    };
    SCRY_REF_PTR(PixelTransferTest);

}


#endif
