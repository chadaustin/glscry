#ifndef SCRY_DRAW_PIXEL_TEST_H
#define SCRY_DRAW_PIXEL_TEST_H


#include "OpenGL.h"
#include "PixelTransferTest.h"


namespace scry {

    class DrawPixelTest : public PixelTransferTest {
    protected:
        ~DrawPixelTest() { }

    public:
        static void bind();

        DrawPixelTest(const char* name)
        : PixelTransferTest(name) {
        }

        void setup() {
            _buffer.resize(getWidth() * getHeight() *
                           getElementCount() * getTypeSize());
        }

        void iterate(ResultSet& results) {
            glDrawPixels(getWidth(), getHeight(),
                         getFormat(), getType(), &_buffer[0]);
            results[0] += getWidth() * getHeight();
            results[1] += getWidth() * getHeight() *
                          getElementCount() * getTypeSize();
        }

    private:
        std::vector<GLubyte> _buffer;
    };
    SCRY_REF_PTR(DrawPixelTest);

}


#endif
