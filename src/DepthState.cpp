#include "DepthState.h"
#include "GLUtility.h"
using namespace boost::python;


namespace scry {

    void DepthState::bind() {
        typedef DepthState C;
        typedef DepthStatePtr CPtr;
        class_<C, CPtr, bases<State>, boost::noncopyable>
            ("DepthState", no_init)
            .def(init<>())
            .add_property("depthTest", &C::getDepthTest, &C::setDepthTest)
            ;

        implicitly_convertible<CPtr, StatePtr>();
    }

    const State& DepthState::getDefault() const {
        static StatePtr ptr = new DepthState;
        return *ptr;
    }

    void DepthState::switchTo(const State& to) const {
        const DepthState& ds = checked_cast_ref<const DepthState&>(to);
        if (_enableDepthTest != ds._enableDepthTest) {
            glSetEnabled(GL_DEPTH_TEST, ds._enableDepthTest);
        }
    }

}
