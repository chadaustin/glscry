#include <boost/python.hpp>
#include "ColorBufferState.h"
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

}
