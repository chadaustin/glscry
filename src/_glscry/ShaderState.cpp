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
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "ShaderState.h"
using namespace boost::python;


namespace scry {

    void bindShader() {
        typedef Shader C;
        typedef ShaderPtr CPtr;
        class_<C, CPtr, boost::noncopyable>("Shader", no_init)
            .def("isSupported", &C::isSupported)
            .staticmethod("isSupported")
            ;

        class_<ShaderList>("ShaderList")
            .def(vector_indexing_suite<ShaderList>())
            ;
    }

    void bindVertexShader() {
        typedef VertexShader C;
        typedef VertexShaderPtr CPtr;
        class_<C, CPtr, bases<Shader>, boost::noncopyable>
            ("VertexShader", no_init)
            .def(init<const string&>())
            .def("isSupported", &C::isSupported)
            .staticmethod("isSupported")
            ;

        implicitly_convertible<CPtr, ShaderPtr>();
    }

    void bindFragmentShader() {
        typedef FragmentShader C;
        typedef FragmentShaderPtr CPtr;
        class_<C, CPtr, bases<Shader>, boost::noncopyable>
            ("FragmentShader", no_init)
            .def(init<const string&>())
            .def("isSupported", &C::isSupported)
            .staticmethod("isSupported")
            ;

        implicitly_convertible<CPtr, ShaderPtr>();
    }
     
    void bindProgram() {
        typedef Program C;
        class_<C, ProgramPtr, boost::noncopyable>("Program", no_init)
            .def(init<const ShaderList&>())
            .def("isSupported", &C::isSupported)
            .staticmethod("isSupported")
            ;
    }
    

    void ShaderState::bind() {
        bindShader();
        bindVertexShader();
        bindFragmentShader();
        bindProgram();

        typedef ShaderState C;
        class_<C, ShaderStatePtr, bases<State>, boost::noncopyable>
            ("ShaderState", no_init)
            .def(init< optional<ProgramPtr> >())
            .def("isSupported", &C::isSupported)
            .staticmethod("isSupported")
            ;

        implicitly_convertible<ShaderStatePtr, StatePtr>();
    }

    ShaderState* ShaderState::clone() const {
        return new ShaderState(*this);
    }
    
    const ShaderState& ShaderState::getDefault() const {
        static ShaderStatePtr ptr = new ShaderState;
        return *ptr;
    }

    inline GLhandleARB handleOf(const ProgramPtr& p) {
        return (p ? p->getHandle() : 0);
    }
    
    void ShaderState::switchTo(const State& to, bool fullStateSwitch) const {
        const ShaderState& ss = checked_cast_ref<const ShaderState&>(to);
        if (fullStateSwitch || _program != ss._program) {
            glUseProgramObjectARB(handleOf(ss._program));
        }
    }

}
