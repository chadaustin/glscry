#include "State.h"
using namespace boost::python;


namespace scry {

    void State::bind() {
        class_<State, StatePtr, boost::noncopyable>("State", no_init);
    }

}
