#ifndef SCRY_COLOR_BUFFER_STATE_H
#define SCRY_COLOR_BUFFER_STATE_H


#include "State.h"


namespace scry {

    class ColorBufferState : public State {
    protected:
        ~ColorBufferState() { }

    public:
        static void bind();

        const State& getDefault() const;
        void switchTo(const State& to) const;

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

    protected:
        bool _writeMask[4];
    };
    SCRY_REF_PTR(ColorBufferState);

}


#endif
