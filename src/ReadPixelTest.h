#ifndef SCRY_READ_PIXEL_TEST_H
#define SCRY_READ_PIXEL_TEST_H


#include "Base.h"
#include "PixelTransferTest.h"


SCRY_BEGIN_NAMESPACE


class ReadPixelTest : public PixelTransferTest {
protected:
    ~ReadPixelTest() { }

public:
    static void bind();

    const char* name() const { return "ReadPixelTest"; }

    void iterate(ResultSet& results) {
        static const int width = 256;
        static const int height = 256;
        static char buffer[width * height * 4];
        glReadPixels(0, 0, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        results[0] += width * height;
    }
};
SCRY_REF_PTR(ReadPixelTest);



SCRY_END_NAMESPACE


#endif
