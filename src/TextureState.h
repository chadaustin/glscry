#ifndef SCRY_TEXTURE_STATE_H
#define SCRY_TEXTURE_STATE_H


#include <vector>
#include "OpenGL.h"
#include "State.h"
#include "Types.h"


namespace scry {

    class Texture : public RefCounted {
    protected:
        ~Texture();

    public:
        static void bind();

        Texture();

        GLuint getHandle() const {
            return _handle;
        }

    private:
        void update();

        // Texture image properties.
        // Default texture is one Mibibyte.
        Inited<size_t, 512>              _width;
        Inited<size_t, 512>              _height;
        Inited<GLint, 4>                 _internalFormat;
        Inited<GLint, 0>                 _border;
        Inited<GLenum, GL_RGBA>          _format;
        Inited<GLenum, GL_UNSIGNED_BYTE> _type;

        // Texture object properties.
        float _minFilter;
        float _magFilter;
        float _minLOD;
        float _maxLOD;
        int   _baseLevel;
        int   _maxLevel;
        float _wrapS;
        float _wrapT;
        float _wrapR;
        Vec4f _borderColor;
        float _priority;

        std::vector<GLubyte> _data;
        GLuint               _handle;
    };
    SCRY_REF_PTR(Texture);


    class TextureState : public State {
    protected:
        ~TextureState() { }

    public:
        TextureState() {
        }

        TextureState(const TextureState& rhs) {
            _texture = rhs._texture;
        }

        static void bind();

        TextureState* clone() const;
        const TextureState& getDefault() const;
        void switchTo(const State& to) const;

        void setTexture(TexturePtr texture) { _texture = texture; }
        TexturePtr getTexture() const       { return _texture; }

    private:
        TexturePtr _texture;
    };
    SCRY_REF_PTR(TextureState);

}


#endif
