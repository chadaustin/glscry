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
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "GLUtility.h"
#include "LightState.h"
using namespace boost::python;


namespace scry {

    void LightState::bind() {
        typedef LightState C;

        scope s = class_<C, LightStatePtr, bases<State>, boost::noncopyable>
            ("LightState", no_init)
            .def(init<>())
            .add_property("enableLighting",
                          &C::getLightingEnabled,
                          &C::setLightingEnabled)
            .def_readwrite("lights", &C::lights)
            ;

        class_<Light>("Light")
            .def_readwrite("enable",               &Light::enable)
            .def_readwrite("ambient",              &Light::ambient)
            .def_readwrite("diffuse",              &Light::diffuse)
            .def_readwrite("specular",             &Light::specular)
            .def_readwrite("position",             &Light::position)
            .def_readwrite("spotDirection",        &Light::spotDirection)
            .def_readwrite("spotExponent",         &Light::spotExponent)
            .def_readwrite("spotCutoff",           &Light::spotCutoff)
            .def_readwrite("constantAttenuation",  &Light::constantAttenuation)
            .def_readwrite("linearAttenuation",    &Light::linearAttenuation)
            .def_readwrite("quadraticAttenuation", &Light::quadraticAttenuation)
            ;

        typedef std::vector<Light> LightList;
        class_<LightList>("LightList")
            .def(vector_indexing_suite<LightList>())
            ;

        implicitly_convertible<LightStatePtr, StatePtr>();
    }

    LightState::LightState() {
        GLint max_lights;
        glGetIntegerv(GL_MAX_LIGHTS, &max_lights);
        lights.resize(max_lights);
        SCRY_ASSERT(lights.size() >= 8); // OpenGL minimum max lights.

        // Light0 is special.
        Light& light0 = lights[0];
        light0.diffuse = Vec4f(1, 1, 1, 1);
        light0.specular = Vec4f(1, 1, 1, 1);
    }

    LightState* LightState::clone() const {
        return new LightState(*this);
    }

    const LightState& LightState::getDefault() const {
        static LightStatePtr state = new LightState;
        return *state;
    }

    void LightState::switchTo(const State& to, bool fullStateSwitch) const {
        const LightState& ls = checked_cast_ref<const LightState&>(to);

        SCRY_ASSERT(lights.size() == ls.lights.size());
        
        if (fullStateSwitch || _enabled != ls._enabled) {
            glSetEnabled(GL_LIGHTING, ls._enabled);
        }
        for (size_t i = 0; i < lights.size(); ++i) {
            lights[i].switchTo(GL_LIGHT0 + i, ls.lights[i], fullStateSwitch);
        }
    }

    void LightState::Light::switchTo(
        GLenum light,
        const Light& to,
        bool fullStateSwitch
    ) const {
#define IF(x) if (fullStateSwitch || x != to.x)
        IF(enable)               glSetEnabled(light, to.enable);
        IF(ambient)              glLightfv(light, GL_AMBIENT,               to.ambient.getData());
        IF(diffuse)              glLightfv(light, GL_DIFFUSE,               to.diffuse.getData());
        IF(specular)             glLightfv(light, GL_SPECULAR,              to.specular.getData());
        IF(position)             glLightfv(light, GL_POSITION,              to.position.getData());
        IF(spotDirection)        glLightfv(light, GL_SPOT_DIRECTION,        to.spotDirection.getData());
        IF(spotExponent)         glLightf (light, GL_SPOT_EXPONENT,         to.spotExponent);
        IF(spotCutoff)           glLightf (light, GL_SPOT_CUTOFF,           to.spotCutoff);
        IF(constantAttenuation)  glLightf (light, GL_CONSTANT_ATTENUATION,  to.constantAttenuation);
        IF(linearAttenuation)    glLightf (light, GL_LINEAR_ATTENUATION,    to.linearAttenuation);
        IF(quadraticAttenuation) glLightf (light, GL_QUADRATIC_ATTENUATION, to.quadraticAttenuation);
    }

}
