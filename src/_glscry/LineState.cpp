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
#include <boost/python.hpp>
#include "GLUtility.h"
#include "LineState.h"
#include "OpenGL.h"
#include "Utility.h"
using namespace boost::python;


namespace scry {

    void LineState::bind() {
        typedef LineState C;
        typedef LineStatePtr CPtr;
        class_<C, CPtr, bases<State>, boost::noncopyable>("LineState", no_init)
            .def(init<>())
            .add_property("enableSmooth", &C::getEnableSmooth, &C::setEnableSmooth)
            .add_property("enableStipple", &C::getEnableStipple, &C::setEnableStipple)
            .add_property("stippleFactor", &C::getStippleFactor, &C::setStippleFactor)
            .add_property("stipplePattern", &C::getStipplePattern, &C::setStipplePattern)
            .add_property("width", &C::getWidth, &C::setWidth)
            ;

        implicitly_convertible<CPtr, StatePtr>();
    }

    LineState* LineState::clone() const {
        return new LineState(*this);
    }

    const LineState& LineState::getDefault() const {
        static LineStatePtr state = new LineState;
        return *state;
    }

    void LineState::switchTo(const State& to,
                             bool fullStateSwitch
    ) const {
        const LineState& ls = checked_cast_ref<const LineState&>(to);

        if (fullStateSwitch || _enableSmooth != ls._enableSmooth) {
            glSetEnabled(GL_LINE_SMOOTH, ls._enableSmooth);
        }
        if (fullStateSwitch || _enableStipple != ls._enableStipple) {
            glSetEnabled(GL_LINE_STIPPLE, ls._enableStipple);
        }
        if (fullStateSwitch ||
            _stippleFactor != ls._stippleFactor ||
            _stipplePattern != ls._stipplePattern
        ) {
            glLineStipple(ls._stippleFactor, ls._stipplePattern);
        }
        if (fullStateSwitch || _width != ls._width) {
            glLineWidth(ls._width);
        }

    }

}
