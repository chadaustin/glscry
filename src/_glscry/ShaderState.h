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
#ifndef SCRY_SHADER_STATE_H
#define SCRY_SHADER_STATE_H


#include <vector>
#include "GLUtility.h"
#include "State.h"
#include "Types.h"


namespace scry {

    inline void compileShader(GLhandleARB shader, const string& source) {
        const GLcharARB* sources[] = { source.c_str() };
        GLint            lengths[] = { source.length() };
        glShaderSourceARB(shader, 1, sources, lengths);

        glCompileShaderARB(shader);
        GLint compiled;
        glGetObjectParameterivARB(
            shader, GL_OBJECT_COMPILE_STATUS_ARB, &compiled);
        if (!compiled) {
            GLint length;
            glGetObjectParameterivARB(
                shader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);
            std::vector<GLcharARB> infoLog(length);
            glGetInfoLogARB(shader, length, 0, &infoLog[0]);
            throw std::runtime_error(string("GLSL Compile error: ") + &infoLog[0]);
        }

        checkOpenGLErrors();
    }


    class Shader : public RefCounted {
    public:
        static bool isSupported() {
            return bool(GLEW_ARB_shader_objects);
        }

        GLhandleARB getHandle() const {
            return _shader;
        }

    protected:
        Shader(GLenum shaderType, const string& source) {
            _shader = glCreateShaderObjectARB(shaderType);
            if (!_shader) {
                throw std::runtime_error("glCreateShaderObjectARB failed");
            }

            compileShader(_shader, source);
        }

        ~Shader() {
            glDeleteObjectARB(_shader);
        }

    private:
        GLhandleARB _shader;
    };
    SCRY_REF_PTR(Shader);

    typedef std::vector<ShaderPtr> ShaderList;


    class VertexShader : public Shader {
    protected:
        ~VertexShader() { }

    public:
        static bool isSupported() {
            return GLEW_ARB_vertex_shader && GLEW_ARB_shading_language_100;
        }

        VertexShader(const string& source)
        : Shader(GL_VERTEX_SHADER_ARB, source) {
        }
    };
    SCRY_REF_PTR(VertexShader);


    class FragmentShader : public Shader {
    protected:
        ~FragmentShader() { }

    public:
        static bool isSupported() {
            return GLEW_ARB_fragment_shader && GLEW_ARB_shading_language_100;
        }

        FragmentShader(const string& source)
        : Shader(GL_FRAGMENT_SHADER_ARB, source) {
        }
    };
    SCRY_REF_PTR(FragmentShader);


    class Program : public RefCounted {
    protected:
        ~Program() {
            glDeleteObjectARB(_program);
        }

    public:
        static bool isSupported() {
            return bool(GLEW_ARB_shader_objects);            
        }

        Program(const ShaderList& shaders) {
            _program = glCreateProgramObjectARB();
            if (!_program) {
                throw std::runtime_error("glCreateProgramObjectARB failed");
            }

            for (size_t i = 0; i < shaders.size(); ++i) {
                glAttachObjectARB(_program, shaders[i]->getHandle());
            }
            glLinkProgramARB(_program);

            GLint linked;
            glGetObjectParameterivARB(
                _program, GL_OBJECT_LINK_STATUS_ARB, &linked);
            if (!linked) {
                GLint length;
                glGetObjectParameterivARB(
                    _program, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);
                std::vector<GLcharARB> infoLog(length);
                glGetInfoLogARB(_program, length, 0, &infoLog[0]);
                throw std::runtime_error(string("GLSL Link error: ") + &infoLog[0]);
            }
        }

        GLhandleARB getHandle() const {
            return _program;
        }

    private:
        GLhandleARB _program;
    };
    SCRY_REF_PTR(Program);


    class ShaderState : public State {
    protected:
        ~ShaderState() { }

    public:
        static void bind();

        static bool isSupported() {
            return bool(GLEW_ARB_shader_objects);
        }

        ShaderState(ProgramPtr program = 0)
        : _program(program) {
        }

        ShaderState(const ShaderState& rhs)
        : _program(rhs._program) {
        }

        ShaderState* clone() const;
        const ShaderState& getDefault() const;
        void switchTo(const State& to, bool fullStateSwitch) const;

    private:
        ProgramPtr _program;
    };
    SCRY_REF_PTR(ShaderState);

}


#endif
