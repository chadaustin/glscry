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
#include "TextureState.h"
using namespace boost::python;


namespace scry {

    void Texture::bind() {

        /// @todo Need to call update whenever a parameter is set!

        typedef Texture C;
        class_<C, TexturePtr, boost::noncopyable>("Texture", no_init)
            .def(init<>())
            .def_readwrite("minFilter",   &C::_minFilter)
            .def_readwrite("magFilter",   &C::_magFilter)
            .def_readwrite("minLOD",      &C::_minLOD)
            .def_readwrite("maxLOD",      &C::_maxLOD)
            .def_readwrite("baseLevel",   &C::_baseLevel)
            .def_readwrite("maxLevel",    &C::_maxLevel)
            .def_readwrite("wrapS",       &C::_wrapS)
            .def_readwrite("wrapT",       &C::_wrapT)
            .def_readwrite("wrapR",       &C::_wrapR)
            .def_readwrite("borderColor", &C::_borderColor)
            .def_readwrite("priority",    &C::_priority)
            ;
    }

    Texture::Texture()
    : _minFilter(GL_NEAREST_MIPMAP_LINEAR)
    , _magFilter(GL_LINEAR)
    , _minLOD(-1000)
    , _maxLOD(1000)
    , _baseLevel(0)
    , _maxLevel(1000)
    , _wrapS(GL_REPEAT)
    , _wrapT(GL_REPEAT)
    , _wrapR(GL_REPEAT)
    , _borderColor(0, 0, 0, 0)
    , _priority(0) {
        glGenTextures(1, &_handle);
        update();
    }

    Texture::~Texture() {
        glDeleteTextures(1, &_handle);
    }

    GLubyte randbyte() {
        return rand() % 256;
    }

    inline void tpf(GLenum name, float value) {
        glTexParameterf(GL_TEXTURE_2D, name, value);
    }
    inline void tpfv(GLenum name, const float* value) {
        glTexParameterfv(GL_TEXTURE_2D, name, value);
    }
    inline void tpi(GLenum name, int value) {
        glTexParameteri(GL_TEXTURE_2D, name, value);
    }

    void Texture::update() {
        glBindTexture(GL_TEXTURE_2D, _handle);

        _data.resize(_width * _height * getTypeSize(_type) * getElementCount(_format));
        std::generate(_data.begin(), _data.end(), randbyte);
        glTexImage2D(
            GL_TEXTURE_2D, 0, _internalFormat, _width, _height,
            _border, _format, _type, &_data[0]);

        tpf(GL_TEXTURE_MIN_FILTER, _minFilter);
        tpf(GL_TEXTURE_MAG_FILTER, _magFilter);
        tpf(GL_TEXTURE_MIN_LOD,    _minLOD);
        tpf(GL_TEXTURE_MAX_LOD,    _maxLOD);
        tpi(GL_TEXTURE_BASE_LEVEL, _baseLevel);
        tpi(GL_TEXTURE_MAX_LEVEL,  _maxLevel);
        tpf(GL_TEXTURE_WRAP_S,     _wrapS);
        tpf(GL_TEXTURE_WRAP_T,     _wrapT);
        tpf(GL_TEXTURE_WRAP_R,     _wrapR);
        tpfv(GL_TEXTURE_BORDER_COLOR, _borderColor.getData());
        tpf(GL_TEXTURE_PRIORITY,   _priority);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextureState::bind() {
        Texture::bind();

        typedef TextureState C;
        typedef TextureStatePtr CPtr;
        class_<C, CPtr, bases<State>, boost::noncopyable>
            ("TextureState", no_init)
            .def(init<>())
            .add_property("texture", &C::getTexture, &C::setTexture)
            ;

        implicitly_convertible<CPtr, StatePtr>();
    }

    TextureState* TextureState::clone() const {
        return new TextureState(*this);
    }

    const TextureState& TextureState::getDefault() const {
        static TextureStatePtr state = new TextureState;
        return *state;
    }

    void TextureState::switchTo(const State& state, bool fullStateSwitch) const {
        const TextureState& ts = checked_cast_ref<const TextureState&>(state);
        if (fullStateSwitch || _texture != ts._texture) {
            if (ts._texture) {
                /// @todo With shaders, you don't need to glEnable the texture.
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, ts._texture->getHandle());
            } else {
                glDisable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }
    }

}
