#ifndef SCRY_GEOMETRY_GENERATOR_H
#define SCRY_GEOMETRY_GENERATOR_H


#include <algorithm>
#include <vector>
#include <gmtl/gmtl.h>
#include "glew.h"
#include "RefCounted.h"


namespace scry {


    template<typename T>
    struct GLTypeConstant { };

    template<>
    struct GLTypeConstant<float> {
        enum { Result = GL_FLOAT };
    };

    template<>
    struct GLTypeConstant<double> {
        enum { Result = GL_DOUBLE };
    };


    struct Triangle {
        // This could become a template argument.
        typedef gmtl::Vec3f Vector;

        Triangle() {
        }

        Triangle(const Vector& v1, const Vector& v2, const Vector& v3) {
            this->v1 = v1;
            this->v2 = v2;
            this->v3 = v3;
        }

        Vector v1, v2, v3;

        enum { Size = Vector::Size };
        enum { TypeConstant = GLTypeConstant<Vector::DataType>::Result };
    };

/*
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
*/

    class GeometryGenerator : public RefCounted {
    protected:
        ~GeometryGenerator() { }

    public:
        static void bind();

        //GeometryGenerator(GLenum primitiveType);

        //void setPositions(ArrayPtr array);


        // Fills the buffer with 'count' triangles.
        virtual void generate(std::vector<Triangle>& buffer, size_t count) const = 0;
    };
    SCRY_REF_PTR(GeometryGenerator);


    class Zeroes : public GeometryGenerator {
    protected:
        ~Zeroes() { }

    public:
        static void bind();

        void generate(std::vector<Triangle>& buffer, size_t count) const {
            buffer.resize(count);
            std::fill(buffer.begin(), buffer.end(), Triangle());
        }
    };
    SCRY_REF_PTR(Zeroes);


    class SmallTriangles : public GeometryGenerator {
    protected:
        ~SmallTriangles() { }

    public:
        static void bind();

        void generate(std::vector<Triangle>& buffer, size_t count) const {
            buffer.resize(count);
            Triangle::Vector v1(0, 0, 0);
            Triangle::Vector v2(0, 1, 0);
            Triangle::Vector v3(1, 1, 0);
            std::fill(buffer.begin(), buffer.end(), Triangle(v1, v2, v3));
        }
    };
    SCRY_REF_PTR(SmallTriangles);

}


#endif
