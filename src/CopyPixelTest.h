#ifndef SCRY_COPY_PIXEL_TEST_H
#define SCRY_COPY_PIXEL_TEST_H


#include "Base.h"
#include "PixelTransferTest.h"


SCRY_BEGIN_NAMESPACE


class CopyPixelTest : public PixelTransferTest {
protected:
    ~CopyPixelTest() { }

public:
    static void bind();

    const char* name() const { return "CopyPixelTest"; }

    void iterate(ResultSet& results) {
        static const int width = 256;
        static const int height = 256;
        glCopyPixels(0, 0, width, height, GL_COLOR);
        results[0] += width * height;
    }
};
SCRY_REF_PTR(CopyPixelTest);


SCRY_END_NAMESPACE


#endif
