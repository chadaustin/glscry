#include <boost/python.hpp>
#include "MaterialState.h"
using namespace boost::python;


namespace scry {

    void MaterialState::bind() {
        typedef MaterialState C;
        scope s = class_<MaterialState, MaterialStatePtr, bases<State>, boost::noncopyable>
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
    
    void MaterialState::apply() {
        front.apply(GL_FRONT);
        back.apply(GL_BACK);
    }
    
    void MaterialState::reset() {
        Material def;
        def.apply(GL_FRONT);
        def.apply(GL_BACK);
    }
    
    void MaterialState::Material::apply(GLenum to) {
        glMaterialfv(to, GL_AMBIENT,   ambient.getData());
        glMaterialfv(to, GL_DIFFUSE,   diffuse.getData());
        glMaterialfv(to, GL_SPECULAR,  specular.getData());
        glMaterialfv(to, GL_EMISSION,  emission.getData());
        glMaterialf (to, GL_SHININESS, shininess);
    }

}
