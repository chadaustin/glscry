#include "LightState.h"
using namespace boost::python;


namespace scry {

    void LightState::bind() {
        class_<LightState, LightStatePtr, bases<State>, boost::noncopyable>
            ("LightState", no_init)
            .def(init<>())
            .def("useLight", &LightState::useLight)
            .def("setAmbient", &LightState::setAmbient);

        implicitly_convertible<LightStatePtr, StatePtr>();
    }

}
