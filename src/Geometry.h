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

        Geometry(GLenum primitiveType);

        GLenum getPrimitiveType() const {
            return _primitiveType;
        }

        ArrayPtr vertices;
        ArrayPtr colors;
        ArrayPtr normals;
        ArrayPtr texcoords;
        ArrayPtr indices;   // Must contain scalars. (Array.getSize() == 1)

    private:
        GLenum _primitiveType;
    };
    SCRY_REF_PTR(Geometry);

}


#endif
