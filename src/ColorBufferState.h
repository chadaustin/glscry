#ifndef SCRY_COLOR_BUFFER_STATE_H
#define SCRY_COLOR_BUFFER_STATE_H


#include "OpenGL.h"
#include "State.h"


namespace scry {

    class ColorBufferState : public State {
    protected:
        ~ColorBufferState() { }

    public:
        static void bind();

        ColorBufferState() {
            _writeMask[0] = true;
            _writeMask[1] = true;
            _writeMask[2] = true;
            _writeMask[3] = true;
        }

        void setWriteMask(bool r, bool g, bool b, bool a) {
            _writeMask[0] = r;
            _writeMask[1] = g;
            _writeMask[2] = b;
            _writeMask[3] = a;
        }

        void apply() {
            glColorMask(_writeMask[0], _writeMask[1], _writeMask[2], _writeMask[3]);
        }

        void reset() {
            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        }

    protected:
        bool _writeMask[4];
    };
    SCRY_REF_PTR(ColorBufferState);

}


#endif
