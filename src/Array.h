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
#ifndef SCRY_ARRAY_H
#define SCRY_ARRAY_H


#include <vector>
#include "GLUtility.h"
#include "RefCounted.h"


namespace scry {

    class ArrayInterface : public RefCounted {
    protected:
        ~ArrayInterface() { }

    public:
        virtual size_t getSize() const = 0;
        virtual GLenum getTypeConstant() const = 0;
        virtual void build(void* buffer, size_t vertexCount) const = 0;
        virtual GLuint getUInt(const void* buffer, size_t offset) const = 0;
        virtual GLdouble getDouble(const void* buffer, size_t offset) const = 0;

        size_t getTypeSize() const;
    };


    template<typename T>
    class Array : public ArrayInterface {
    protected:
        ~Array() { }

    public:
        typedef T Type;
        typedef std::vector<T> List;

        Array(size_t size) {
            _size = size;
        }

        size_t getSize() const {
            return _size;
        }

        GLenum getTypeConstant() const {
            return GLTypeConstant<Type>::Result;
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
                if (repeat.empty()) {
                    array[i] = Type();
                } else {
                    array[i] = repeat[repeat_i % repeat.size()];
                }
                    
                // Add in the offset.
                if (!offset.empty()) {
                    size_t offset_i = repeat_i % offset.size();
                    array[i] += offset[offset_i] * (repeat_i / offset.size());
                }

                ++i;
                ++repeat_i;
            }
        }

        GLuint getUInt(const void* buffer, size_t offset) const {
            const Type* array = static_cast<const Type*>(buffer);
            return static_cast<GLuint>(array[offset]);
        }

        GLdouble getDouble(const void* buffer, size_t offset) const {
            const Type* array = static_cast<const Type*>(buffer);
            return static_cast<GLdouble>(array[offset]);
        }

        List initial;
        List repeat;
        List offset;

    private:
        size_t _size;
    };
    typedef boost::intrusive_ptr<ArrayInterface> ArrayPtr;


    void bindArrayTypes();


    using ::glVertexPointer;
    using ::glColorPointer;
    using ::glNormalPointer;
    using ::glTexCoordPointer;

    inline void glVertexPointer(ArrayPtr array, const void* buffer) {
        glVertexPointer(array->getSize(), array->getTypeConstant(), 0, buffer);
    }

    inline void glColorPointer(ArrayPtr array, const void* buffer) {
        glColorPointer(array->getSize(), array->getTypeConstant(), 0, buffer);
    }

    inline void glNormalPointer(ArrayPtr array, const void* buffer) {
        SCRY_ASSERT(array->getSize() == 3);
        glNormalPointer(array->getTypeConstant(), 0, buffer);
    }

    inline void glTexCoordPointer(ArrayPtr array, const void* buffer) {
        glTexCoordPointer(array->getSize(), array->getTypeConstant(), 0, buffer);
    }

}


#endif
