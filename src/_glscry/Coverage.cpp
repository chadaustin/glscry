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
#include <stdexcept>
#include "Coverage.h"
#include "GLUtility.h"
#include "Types.h"


namespace scry {


    short  myabs(short s)  { return abs(s);  }
    int    myabs(int i)    { return abs(i);  }
    float  myabs(float f)  { return fabs(f); }
    double myabs(double d) { return fabs(d); }


    template<GLenum primitiveType, typename dataType>
    struct CoverageCalculator;


    // POINTS
    template<typename dataType>
    struct CoverageCalculator<GL_POINTS, dataType> {
        static Uint64 calculate(
            size_t size,
            size_t vertexCount,
            const dataType* data
        ) {
            // Assume each point takes up one pixel.
            return vertexCount;
        }
    };


    // LINES
    template<typename dataType>
    struct CoverageCalculator<GL_LINES, dataType> {
        static Uint64 calculate(
            size_t size,
            size_t vertexCount,
            const dataType* data
        ) {
            const dataType* v = data;

            Uint64 total = 0;
            for (size_t i = 0; (i + 1) < vertexCount; i += 2, v += 2 * size) {
                total += Uint64(std::max(myabs(v[0] - v[size]),
                                         myabs(v[1] - v[size + 1])));
            }
            return total;
        }
    };


    // LINE_STRIP
    template<typename dataType>
    struct CoverageCalculator<GL_LINE_STRIP, dataType> {
        static Uint64 calculate(
            size_t size,
            size_t vertexCount,
            const dataType* data
        ) {
            if (vertexCount < 2) {
                return 0;
            }

            typedef gmtl::Vec<dataType, 2> Vec;
            const dataType* v = data;

            Uint64 total = 0;
            Vec last(v[0], v[1]); v += size;
            for (size_t i = 1; i < vertexCount; ++i, v += size) {
                total += Uint64(std::max(myabs(v[0] - last[0]),
                                         myabs(v[1] - last[1])));
                last = Vec(v[0], v[1]);
            }
            return total;
        }
    };


    // LINE_LOOP
    template<typename dataType>
    struct CoverageCalculator<GL_LINE_LOOP, dataType> {
        static Uint64 calculate(
            size_t size,
            size_t vertexCount,
            const dataType* data
        ) {
            if (vertexCount < 2) {
                return 0;
            }

            typedef gmtl::Vec<dataType, 2> Vec;
            const dataType* v = data;

            Uint64 total = 0;
            Vec last(v[0], v[1]);
            Vec first(last);
            for (size_t i = 1; i < vertexCount; ++i, v += size) {
                total += Uint64(std::max(myabs(v[0] - last[0]),
                                         myabs(v[1] - last[1])));
                last = Vec(v[0], v[1]);
            }
            total += Uint64(std::max(myabs(first[0] - last[0]),
                                     myabs(first[1] - last[1])));
            return total;
        }
    };


    template<typename dataType>
    Uint64 getTriangleArea(gmtl::Vec<dataType, 2> a,
                           gmtl::Vec<dataType, 2> b,
                           gmtl::Vec<dataType, 2> c
    ) {
        // http://www.btinternet.com/~se16/hgb/triangle.htm    
        float ab = b[0] * a[1] - a[0] * b[1];
        float bc = c[0] * b[1] - b[0] * c[1];
        float ac = a[0] * c[1] - c[0] * a[1];
        return Uint64(myabs(ab + bc + ac) / 2);
    }


    // TRIANGLES
    template<typename dataType>
    struct CoverageCalculator<GL_TRIANGLES, dataType> {
        static Uint64 calculate(
            size_t size,
            size_t vertexCount,
            const dataType* data
        ) {
            typedef gmtl::Vec<dataType, 2> Vec;
            const dataType* v = data;

            Uint64 total = 0;
            for (size_t i = 0; (i + 2) < vertexCount; i += 3, v += size * 3) {
                total += getTriangleArea(
                    Vec(v[size * 0], v[size * 0 + 1]),
                    Vec(v[size * 1], v[size * 1 + 1]),
                    Vec(v[size * 2], v[size * 2 + 1]));
            }
            return total;
        }
    };


    // TRIANGLE_STRIP
    template<typename dataType>
    struct CoverageCalculator<GL_TRIANGLE_STRIP, dataType> {
        static Uint64 calculate(
            size_t size,
            size_t vertexCount,
            const dataType* data
        ) {
            typedef gmtl::Vec<dataType, 2> Vec;
            const dataType* v = data;

            if (vertexCount < 3) {
                return 0;
            }

            Vec v0(v[0], v[1]); v += size;
            Vec v1(v[0], v[1]); v += size;

            Uint64 total = 0;
            for (size_t i = 2; i < vertexCount; i += 3, v += size * 3) {
                Vec v2(v[0], v[1]);
                total += getTriangleArea(v0, v1, v2);
                v0 = v1;
                v1 = v2;
            }
            return total;
        }
    };


    // TRIANGLE_FAN
    template<typename dataType>
    struct CoverageCalculator<GL_TRIANGLE_FAN, dataType> {
        static Uint64 calculate(
            size_t size,
            size_t vertexCount,
            const dataType* data
        ) {
            if (vertexCount < 2) {
                return 0;
            }

            typedef gmtl::Vec<dataType, 2> Vec;
            const dataType* v = data;

            Vec first(v[0], v[1]); v += size;
            Vec last (v[0], v[1]); v += size;

            Uint64 total = 0;
            for (size_t i = 1; i < vertexCount; ++i, v += size) {
                Vec current(v[0], v[1]);
                total += getTriangleArea(first, last, current);
                last = current;
            }
            return total;
        }
    };


    // QUADS
    template<typename dataType>
    struct CoverageCalculator<GL_QUADS, dataType> {
        static Uint64 calculate(
            size_t size,
            size_t vertexCount,
            const dataType* data
        ) {
            typedef gmtl::Vec<dataType, 2> Vec;
            const dataType* v = data;

            Uint64 total = 0;
            for (size_t i = 0; (i + 3) < vertexCount; i += 4) {
                Vec v1(v[0], v[1]); v += size;
                Vec v2(v[0], v[1]); v += size;
                Vec v3(v[0], v[1]); v += size;
                Vec v4(v[0], v[1]); v += size;
                total += getTriangleArea(v1, v2, v3);
                total += getTriangleArea(v1, v3, v4);
            }
            return total;
        }
    };


    // QUAD_STRIP
    template<typename dataType>
    struct CoverageCalculator<GL_QUAD_STRIP, dataType> {
        static Uint64 calculate(
            size_t size,
            size_t vertexCount,
            const dataType* data
        ) {
            if (vertexCount < 4) {
                return 0;
            }

            typedef gmtl::Vec<dataType, 2> Vec;
            const dataType* v = data;

            Vec v1(v[0], v[1]); v += size;
            Vec v2(v[0], v[1]); v += size;

            Uint64 total = 0;
            for (size_t i = 2; (i + 1) < vertexCount; i += 2) {
                Vec v3(v[0], v[1]); v += size;
                Vec v4(v[0], v[1]); v += size;
                total += getTriangleArea(v1, v2, v3);
                total += getTriangleArea(v1, v3, v4);
                v1 = v3;
                v2 = v4;
            }
            return total;
        }
    };


    // POLYGON
    template<typename dataType>
    struct CoverageCalculator<GL_POLYGON, dataType> {
        static Uint64 calculate(
            size_t size,
            size_t vertexCount,
            const dataType* data
        ) {
            if (vertexCount < 3) {
                return 0;
            }

            typedef gmtl::Vec<dataType, 2> Vec;
            const dataType* v = data;
            Vec first(v[0], v[1]); v += size;
            Vec last (v[0], v[1]); v += size;

            Uint64 total = 0;
            for (size_t i = 2; i < vertexCount; ++i) {
                Vec current(v[0], v[1]); v += size;
                total += getTriangleArea(first, last, current);
                last = current;
            }
            return total;
        }
    };


    // Stupid hack so we can partially specialize "functions".
    template<GLenum primitiveType, typename dataType>
    Uint64 calculateCoverage(
        size_t size,
        size_t vertexCount,
        const void* data
    ) {
        return CoverageCalculator<primitiveType, dataType>::calculate(
            size, vertexCount, static_cast<const dataType*>(data));
    }


    template<GLenum primitiveType>
    Uint64 calculateCoverage(
        GLenum dataType,
        size_t size,
        size_t vertexCount,
        const void* data
    ) {
#define SCRY_SPECIALIZE_DATA_TYPE(type)                                 \
        case type: return calculateCoverage<primitiveType,              \
            typename GLType<type>::Result>(size, vertexCount, data)

        switch (dataType) {
            SCRY_SPECIALIZE_DATA_TYPE(GL_SHORT);
            SCRY_SPECIALIZE_DATA_TYPE(GL_INT);
            SCRY_SPECIALIZE_DATA_TYPE(GL_FLOAT);
            SCRY_SPECIALIZE_DATA_TYPE(GL_DOUBLE);
            default: throw std::runtime_error("Coverage: unknown data type");
        }
    }



    Uint64 calculateCoverage(
        GLenum primitiveType,
        GLenum dataType,
        size_t size,
        size_t vertexCount,
        const void* data
    ) {
#define SCRY_SPECIALIZE_PRIMITIVE_TYPE(type)                            \
        case type: return calculateCoverage<type>(dataType, size, vertexCount, data)

        switch (primitiveType) {
            SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_POINTS);
            SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_LINES);
            SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_LINE_STRIP);
            SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_LINE_LOOP);
            SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_TRIANGLES);
            SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_TRIANGLE_STRIP);
            SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_TRIANGLE_FAN);
            SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_QUADS);
            SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_QUAD_STRIP);
            SCRY_SPECIALIZE_PRIMITIVE_TYPE(GL_POLYGON);
            default: throw std::runtime_error("Invalid primitive type in calculateCoverage");
        }
    }

}
