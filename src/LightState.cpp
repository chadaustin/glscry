#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "LightState.h"
using namespace boost::python;


namespace scry {

    void LightState::bind() {
        scope s = class_<LightState, LightStatePtr, bases<State>,
                         boost::noncopyable>
            ("LightState", no_init)
            .def(init<>())
            .def_readwrite("lights", &LightState::lights)
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

    void LightState::apply() {
        glEnable(GL_LIGHTING);
        for (size_t i = 0; i < lights.size(); ++i) {
            lights[i].apply(GL_LIGHT0 + i);
        }
    }

    void LightState::reset() {
        for (size_t i = 0; i < lights.size(); ++i) {
            glDisable(GL_LIGHT0 + i);
        }
        glDisable(GL_LIGHTING);
    }

    void LightState::Light::apply(GLenum light) {
        if (enable) {
            glEnable (light);
            glLightfv(light, GL_AMBIENT,               ambient.getData());
            glLightfv(light, GL_DIFFUSE,               diffuse.getData());
            glLightfv(light, GL_SPECULAR,              specular.getData());
            glLightfv(light, GL_POSITION,              position.getData());
            glLightfv(light, GL_SPOT_DIRECTION,        spotDirection.getData());
            glLightf (light, GL_SPOT_EXPONENT,         spotExponent);
            glLightf (light, GL_SPOT_CUTOFF,           spotCutoff);
            glLightf (light, GL_CONSTANT_ATTENUATION,  constantAttenuation);
            glLightf (light, GL_LINEAR_ATTENUATION,    linearAttenuation);
            glLightf (light, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
        } else {
            glDisable(light);
        }
    }

}
