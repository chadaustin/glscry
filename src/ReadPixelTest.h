#ifndef SCRY_READ_PIXEL_TEST_H
#define SCRY_READ_PIXEL_TEST_H


#include "OpenGL.h"
#include "PixelTransferTest.h"


namespace scry {

    class ReadPixelTest : public PixelTransferTest {
    protected:
        ~ReadPixelTest() { }

    public:
        static void bind();

        ReadPixelTest(const char* name)
        : PixelTransferTest(name) {
        }

        void iterate(ResultSet& results) {
            static const int width = 256;
            static const int height = 256;
            static char buffer[width * height * 4];
            glReadPixels(0, 0, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
            results[0] += width * height;
        }
    };
    SCRY_REF_PTR(ReadPixelTest);

}


#endif
