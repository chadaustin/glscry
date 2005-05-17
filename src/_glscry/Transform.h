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
#ifndef SCRY_TRANSFORM_H
#define SCRY_TRANSFORM_H


#include "RefCounted.h"
#include "Types.h"


namespace scry {

    class Transform : public RefCounted {
    protected:
        ~Transform() { }

    public:
        /// Binds all classes in this file.
        static void bind();

        /// Applies this transform to the currently selected matrix.
        virtual void apply() = 0;
    };
    SCRY_REF_PTR(Transform);


    class IdentityTransform : public Transform {
    public:
        void apply();
    };
    SCRY_REF_PTR(IdentityTransform);


    class MatrixTransform : public Transform {
    public:
        MatrixTransform(const Matrix44f& matrix)
        : _matrix(matrix) {
        }

        void apply();

    private:
        Matrix44f _matrix;
    };
    SCRY_REF_PTR(MatrixTransform);

}


#endif
