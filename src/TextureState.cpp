#include <boost/python.hpp>
#include "GLUtility.h"
#include "TextureState.h"
using namespace boost::python;


namespace scry {

    void Texture::bind() {
        typedef Texture C;
        class_<C, TexturePtr, boost::noncopyable>("Texture", no_init)
            .def(init<>())
            ;
    }

    Texture::Texture() {
        glGenTextures(1, &_handle);
        update();
    }

    Texture::~Texture() {
        glDeleteTextures(1, &_handle);
    }

    void Texture::apply() {
        glBindTexture(GL_TEXTURE_2D, _handle);
    }
    
    GLubyte randbyte() {
        return rand() % 256;
    }

    void Texture::update() {
        glBindTexture(GL_TEXTURE_2D, _handle);

        _data.resize(_width * _height * getTypeSize(_type) * getElementCount(_format));
        std::generate(_data.begin(), _data.end(), randbyte);
        glTexImage2D(
            GL_TEXTURE_2D, 0, _internalFormat, _width, _height,
            _border, _format, _type, &_data[0]);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextureState::bind() {
        Texture::bind();

        typedef TextureState C;
        class_<C, TextureStatePtr, bases<State>, boost::noncopyable>
            ("TextureState", no_init)
            .def(init<>())
            .add_property("texture", &C::getTexture, &C::setTexture)
            ;
    }

    void TextureState::apply() {
        if (_texture) {
            glEnable(GL_TEXTURE_2D);
            _texture->apply();
        } else {
            reset();
        }
    }

    void TextureState::reset() {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }

}
