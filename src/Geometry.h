#ifndef SCRY_GEOMETRY_H
#define SCRY_GEOMETRY_H


#include <algorithm>
#include <vector>
#include <gmtl/gmtl.h>
#include "glew.h"
#include "RefCounted.h"


namespace scry {


    class Array : public RefCounted {
    protected:
        ~Array() { }

    public:
        static void bind();

        Array();

    private:
        std::vector<float> _data;    
    };
    SCRY_REF_PTR(Array);


    class Geometry : public RefCounted {
    protected:
        ~Geometry() { }

    public:
        static void bind();

        Geometry(GLenum primitiveType);

        void setVertices(ArrayPtr array) { _vertices = array; }
        ArrayPtr getVertices() const     { return _vertices; }

    private:
        GLenum _primitiveType;
        ArrayPtr _vertices;
    };
    SCRY_REF_PTR(Geometry);

}


#endif
