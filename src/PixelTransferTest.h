#ifndef SCRY_PIXEL_TRANSFER_TEST
#define SCRY_PIXEL_TRANSFER_TEST


#include "Base.h"
#include "Test.h"


SCRY_BEGIN_NAMESPACE

class PixelTransferTest : public Test {
public:
    SCRY_BEGIN_RESULT_DESCS()
        SCRY_RESULT_DESC("PixelRate", "pixels/sec")
    SCRY_END_RESULT_DESCS()
};

SCRY_END_NAMESPACE


#endif
