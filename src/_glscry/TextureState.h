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
        static void bind();

        TextureState();

        TextureState(const TextureState& rhs) {
            _textures = rhs._textures;
        }

        TextureState* clone() const;
        const TextureState& getDefault() const;
        void switchTo(const State& to, bool fullStateSwitch) const;

        size_t getTextureCount() const {
            return _textures.size();
        }

        TexturePtr getTexture(size_t i) const {
            SCRY_ASSERT(i < _textures.size());
            return _textures[i];
        }

        void setTexture(size_t i, const TexturePtr& p) {
            SCRY_ASSERT(i < _textures.size());
            _textures[i] = p;
        }

        TexturePtr getSingleTexture() const {
            return getTexture(0);
        }

        void setSingleTexture(const TexturePtr& p) {
            setTexture(0, p);
        }

    private:
        typedef std::vector<TexturePtr> TextureList;
        TextureList _textures;
    };
    SCRY_REF_PTR(TextureState);

}


#endif
