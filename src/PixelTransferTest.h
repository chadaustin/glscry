#ifndef TRIAGARA_PIXEL_TRANSFER_TEST
#define TRIAGARA_PIXEL_TRANSFER_TEST


#include "Base.h"
#include "Test.h"


TRIAGARA_BEGIN_NAMESPACE

class PixelTransferTest : public Test {
public:
    TRIAGARA_BEGIN_RESULT_DESCS()
        TRIAGARA_RESULT_DESC("PixelRate", "pixels/sec")
    TRIAGARA_END_RESULT_DESCS()
};

TRIAGARA_END_NAMESPACE


#endif
