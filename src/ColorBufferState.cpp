#include <boost/python.hpp>
#include "ColorBufferState.h"
#include "OpenGL.h"
#include "Utility.h"
using namespace boost::python;


namespace scry {

    void ColorBufferState::bind() {
        class_<ColorBufferState, ColorBufferStatePtr, bases<State>, boost::noncopyable>
            ("ColorBufferState", no_init)
            .def(init<>())
            .def("setWriteMask", &ColorBufferState::setWriteMask)
            ;

        implicitly_convertible<ColorBufferStatePtr, StatePtr>();
    }

    ColorBufferState* ColorBufferState::clone() const {
        return new ColorBufferState(*this);
    }

    const ColorBufferState& ColorBufferState::getDefault() const {
        static ColorBufferStatePtr state = new ColorBufferState;
        return *state;
    }

    void ColorBufferState::switchTo(const State& to) const {
        const ColorBufferState& cbs = checked_cast_ref<const ColorBufferState&>(to);
        if (_writeMask[0] != cbs._writeMask[0] ||
            _writeMask[1] != cbs._writeMask[1] ||
            _writeMask[2] != cbs._writeMask[2] ||
            _writeMask[3] != cbs._writeMask[3]
        ) {
            const bool* wm = cbs._writeMask;
            glColorMask(wm[0], wm[1], wm[2], wm[3]);
        }
    }

}
