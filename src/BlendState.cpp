#include "BlendState.h"
#include "GLUtility.h"
using namespace boost::python;


namespace scry {

    void BlendState::bind() {
        typedef BlendState C;
        typedef BlendStatePtr CPtr;
        class_<C, CPtr, bases<State>, boost::noncopyable>
            ("BlendState", no_init)
            .def(init<>())
            .add_property("enableBlend", &C::getEnableBlend, &C::setEnableBlend)
            .add_property("srcFactor", &C::getSrcFactor, &C::setSrcFactor)
            .add_property("dstFactor", &C::getDstFactor, &C::setDstFactor)
            ;

        implicitly_convertible<CPtr, StatePtr>();
    }

    BlendState* BlendState::clone() const {
        return new BlendState(*this);
    }

    const BlendState& BlendState::getDefault() const {
        static BlendStatePtr ptr = new BlendState;
        return *ptr;
    }

    void BlendState::switchTo(const State& to, bool fullStateSwitch) const {
        const BlendState& ds = checked_cast_ref<const BlendState&>(to);
        if (fullStateSwitch || _enableBlend != ds._enableBlend) {
            glSetEnabled(GL_BLEND, ds._enableBlend);
        }

        if (fullStateSwitch ||
            _srcFactor != ds._srcFactor ||
            _dstFactor != ds._dstFactor
        ) {
            glBlendFunc(ds._srcFactor, ds._dstFactor);
        }

    }

}
