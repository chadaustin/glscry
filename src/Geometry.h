#ifndef SCRY_GEOMETRY_H
#define SCRY_GEOMETRY_H


#include <algorithm>
#include <vector>
#include <gmtl/gmtl.h>
#include "glew.h"
#include "GLUtility.h"
#include "RefCounted.h"


namespace scry {


    class Array : public RefCounted {
    protected:
        ~Array() { }

    public:
        typedef float Type;
        typedef std::vector<Type> List;

        static void bind();

        Array(size_t size) {
            _size = size;
        }

        size_t getSize() const {
            return _size;
        }

        GLenum getTypeConstant() const {
            return GLTypeConstant<Type>::Result;
        }

        size_t getTypeSize() const {
            switch (getTypeConstant()) {
                case GL_BITMAP:         return 0; // ??
                case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
                case GL_BYTE:           return sizeof(GLbyte);
                case GL_UNSIGNED_SHORT: return sizeof(GLushort);
                case GL_SHORT:          return sizeof(GLshort);
                case GL_UNSIGNED_INT:   return sizeof(GLuint);
                case GL_INT:            return sizeof(GLint);
                case GL_FLOAT:          return sizeof(GLfloat);
                case GL_DOUBLE:         return sizeof(GLdouble);
                default:                return 0;
            }
        }

        void build(void* buffer, size_t vertexCount) const {
            Type* array = static_cast<Type*>(buffer);
            size_t i = 0;

            // Fill with initial values.
            while (i < initial.size() && i < vertexCount) {
                array[i++] = initial[i];
            }

            // Now repeat.
            size_t repeat_i = 0;
            while (i < vertexCount) {
                array[i] = repeat[repeat_i % repeat.size()];

                // Add in the offset.
                if (!offset.empty()) {
                    size_t offset_i = repeat_i % offset.size();
                    array[i] += offset[offset_i] * (repeat_i / offset.size());
                }

                ++i;
                ++repeat_i;
            }
        }

        List initial;
        List repeat;
        List offset;

    private:
        size_t _size;
    };
    SCRY_REF_PTR(Array);


    class Geometry : public RefCounted {
    protected:
        ~Geometry() { }

    public:
        static void bind();

        Geometry(GLenum primitiveType);

        GLenum getPrimitiveType() const {
            return _primitiveType;
        }

        ArrayPtr vertices;
        ArrayPtr colors;
        ArrayPtr normals;
        ArrayPtr texcoords;

    private:
        GLenum _primitiveType;
    };
    SCRY_REF_PTR(Geometry);

}


#endif
