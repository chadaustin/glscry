#ifndef SCRY_COPY_PIXEL_TEST_H
#define SCRY_COPY_PIXEL_TEST_H


#include "OpenGL.h"
#include "PixelTransferTest.h"


namespace scry {

    class CopyPixelTest : public PixelTransferTest {
    protected:
        ~CopyPixelTest() { }

    public:
        static void bind();

        CopyPixelTest(const char* name)
        : PixelTransferTest(name) {
        }

        void setCopyType(GLenum copyType) { _copyType = copyType; }
        GLenum getCopyType() const        { return _copyType; }

        void iterate(ResultSet& results) {
            glCopyPixels(0, 0, getWidth(), getHeight(), getCopyType());
            results[0] += getWidth() * getHeight();
        }

    private:
        Inited<GLenum, GL_COLOR> _copyType;
    };
    SCRY_REF_PTR(CopyPixelTest);

}


#endif
