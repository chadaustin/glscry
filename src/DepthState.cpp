/* [Begin Copyright Header]
 *
 * GLScry - OpenGL Performance Analysis Tool
 * Copyright (C) 2004-2005  Iowa State University
 * 
 * This software is licensed under the terms of the GNU Lesser Public
 * License, version 2.1, as published by the Free Software Foundation.  
 * See the file COPYRIGHT.txt for details.
 * 
 * Authors:
 *   Chad Austin <aegisk@iastate.edu>
 *   Dirk Reiners <dreiners@iastate.edu>
 *
 * [End Copyright Header] */
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
            .add_property("enableDepthTest", &C::getEnableDepthTest, &C::setEnableDepthTest)
            .add_property("depthFunc", &C::getDepthFunc, &C::setDepthFunc)
            .add_property("depthMask", &C::getDepthMask, &C::setDepthMask)
            ;

        implicitly_convertible<CPtr, StatePtr>();
    }

    DepthState* DepthState::clone() const {
        return new DepthState(*this);
    }

    const DepthState& DepthState::getDefault() const {
        static DepthStatePtr ptr = new DepthState;
        return *ptr;
    }

    void DepthState::switchTo(const State& to, bool fullStateSwitch) const {
        const DepthState& ds = checked_cast_ref<const DepthState&>(to);
        if (fullStateSwitch ||
            _enableDepthTest != ds._enableDepthTest
        ) {
            glSetEnabled(GL_DEPTH_TEST, ds._enableDepthTest);
        }

        if (fullStateSwitch || _depthFunc != ds._depthFunc
        ) {
            glDepthFunc(ds._depthFunc);
        }

        if (fullStateSwitch || _depthMask != ds._depthMask
        ) {
            glDepthMask(ds._depthMask);
        }

    }

}
