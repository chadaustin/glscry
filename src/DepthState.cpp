#include "DepthState.h"
using namespace boost::python;


namespace scry {

    void DepthState::bind() {
        class_<DepthState, DepthStatePtr, bases<State>, boost::noncopyable>
            ("DepthState", no_init)
            .def(init<>());

        implicitly_convertible<DepthStatePtr, StatePtr>();
    }

}
