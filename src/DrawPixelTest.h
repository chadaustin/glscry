#ifndef SCRY_DRAW_PIXEL_TEST_H
#define SCRY_DRAW_PIXEL_TEST_H


#include "Base.h"
#include "PixelTransferTest.h"


SCRY_BEGIN_NAMESPACE


class DrawPixelTest : public PixelTransferTest {
protected:
    ~DrawPixelTest() { }

public:
    static void bind();

    DrawPixelTest(const char* name)
    : PixelTransferTest(name) {
    }

    const char* name() const { return "DrawPixelTest"; }

    void iterate(ResultSet& results) {
        static const int width = 256;
        static const int height = 256;
        static char buffer[width * height * 4];
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        results[0] += width * height;
    }
};
SCRY_REF_PTR(DrawPixelTest);


SCRY_END_NAMESPACE


#endif
