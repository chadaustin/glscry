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
#include "MaterialState.h"
using namespace boost::python;


namespace scry {

    void MaterialState::bind() {
        typedef MaterialState C;
        scope s = class_<MaterialState, MaterialStatePtr, bases<State>,
                         boost::noncopyable>
            ("MaterialState", no_init)
            .def(init<>())
            .def_readwrite("front", &C::front)
            .def_readwrite("back",  &C::back)
            ;

        typedef C::Material CM;
        class_<C::Material>("Material")
            .def_readwrite("ambient",   &CM::ambient)
            .def_readwrite("diffuse",   &CM::diffuse)
            .def_readwrite("specular",  &CM::specular)
            .def_readwrite("emission",  &CM::emission)
            .def_readwrite("shininess", &CM::shininess)
            ;

        implicitly_convertible<MaterialStatePtr, StatePtr>();
    }

    MaterialState* MaterialState::clone() const {
        return new MaterialState(*this);
    }
    
    const MaterialState& MaterialState::getDefault() const {
        static MaterialStatePtr ptr = new MaterialState;
        return *ptr;
    }
    
    void MaterialState::switchTo(const State& to, bool fullStateSwitch) const {
        const MaterialState& ms = checked_cast_ref<const MaterialState&>(to);
        front.switchTo(ms.front, GL_FRONT, fullStateSwitch);
        back .switchTo(ms.back,  GL_BACK,  fullStateSwitch);
    }

    void MaterialState::Material::switchTo(
        const Material& m,
        GLenum face,
        bool fullStateSwitch
    ) const {
        if (fullStateSwitch || ambient   != m.ambient)
            glMaterialfv(face, GL_AMBIENT,   ambient.getData());
        if (fullStateSwitch || diffuse   != m.diffuse)
            glMaterialfv(face, GL_DIFFUSE,   diffuse.getData());
        if (fullStateSwitch || specular  != m.specular)
            glMaterialfv(face, GL_SPECULAR,  specular.getData());
        if (fullStateSwitch || emission  != m.emission)
            glMaterialfv(face, GL_EMISSION,  emission.getData());
        if (fullStateSwitch || shininess != m.shininess)
            glMaterialf (face, GL_SHININESS, shininess);
    }

}
