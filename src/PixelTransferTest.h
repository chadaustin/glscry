#ifndef SCRY_PIXEL_TRANSFER_TEST
#define SCRY_PIXEL_TRANSFER_TEST


#include "Base.h"
#include "Test.h"


SCRY_BEGIN_NAMESPACE

class PixelTransferTest : public Test {
protected:
    ~PixelTransferTest() { }

public:
    static void bind();

    PixelTransferTest(const char* name)
    : Test(name) {
    }

    SCRY_BEGIN_RESULT_DESCS()
        SCRY_RESULT_DESC("PixelRate", "pixels/sec")
    SCRY_END_RESULT_DESCS()
};
SCRY_REF_PTR(PixelTransferTest);

SCRY_END_NAMESPACE


#endif
