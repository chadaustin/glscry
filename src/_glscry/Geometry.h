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
#ifndef SCRY_GEOMETRY_H
#define SCRY_GEOMETRY_H


#include "Array.h"
#include "GLUtility.h"
#include "OpenGL.h"
#include "RefCounted.h"


namespace scry {

    class Geometry : public RefCounted {
    protected:
        ~Geometry() { }

    public:
        static void bind();

        Geometry(GLenum primitiveType, size_t batchSize);

        GLenum getPrimitiveType() const {
            return _primitiveType;
        }

        size_t getBatchSize() const {
            return _batchSize;
        }

        void setBatchSize(size_t batchSize) {
            _batchSize = batchSize;
        }

        typedef std::vector<ArrayPtr> ArrayPtrList;

        /**
         * Must contain scalar integers -- that is, indices.getSize()
         * == 1 and indices.getTypeConstant() is an integer type.
         *
         * If set to null, the attribute arrays are drawn directly.
         * Otherwise, 'indices' contains indices into the other
         * arrays.
         */
        ArrayPtr indices;

        ArrayPtr vertices;
        ArrayPtr colors;
        ArrayPtr normals;
        ArrayPtrList texcoords;

    private:
        GLenum _primitiveType;
        size_t _batchSize;

        // Queried on creation.
        size_t _maxTextureUnits;
    };
    SCRY_REF_PTR(Geometry);

}


#endif
