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
        size_t getElementCount() const {
            switch (_format.get()) {
                case GL_COLOR_INDEX:     return 1;
                case GL_STENCIL_INDEX:   return 1;
                case GL_DEPTH_COMPONENT: return 1;
                case GL_RED:             return 1;
                case GL_GREEN:           return 1;
                case GL_BLUE:            return 1;
                case GL_ALPHA:           return 1;
                case GL_RGB:             return 3;
                case GL_BGR:             return 3;
                case GL_RGBA:            return 4;
                case GL_BGRA:            return 4;
                case GL_LUMINANCE:       return 1;
                case GL_LUMINANCE_ALPHA: return 2;
                default: SCRY_ASSERT(false && "Invalid format"); return 0;
            }
        }

        size_t getTypeSize() const {
            return scry::getTypeSize(_type);
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
