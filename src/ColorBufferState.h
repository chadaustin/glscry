#ifndef SCRY_COLOR_BUFFER_STATE_H
#define SCRY_COLOR_BUFFER_STATE_H


#include <algorithm>
#include "State.h"


namespace scry {

    class ColorBufferState : public State {
    protected:
        ~ColorBufferState() { }

    public:
        static void bind();

        ColorBufferState* clone() const;
        const ColorBufferState& getDefault() const;
        void switchTo(const State& to) const;

        ColorBufferState() {
            std::fill(_writeMask, _writeMask + 4, true);
        }

        ColorBufferState(const ColorBufferState& rhs) {
            std::copy(rhs._writeMask, rhs._writeMask + 4, _writeMask);
        }

        void setWriteMask(bool r, bool g, bool b, bool a) {
            _writeMask[0] = r;
            _writeMask[1] = g;
            _writeMask[2] = b;
            _writeMask[3] = a;
        }

    private:
        bool _writeMask[4];
    };
    SCRY_REF_PTR(ColorBufferState);

}


#endif
