#ifndef SCRY_GEOMETRY_TEST_H
#define SCRY_GEOMETRY_TEST_H


#include "Base.h"
#include "Geometry.h"
#include "Test.h"


SCRY_BEGIN_NAMESPACE

class GeometryTest : public Test {
protected:
    ~GeometryTest() { }

public:
    SCRY_BEGIN_RESULT_DESCS()
        SCRY_RESULT_DESC("VertexRate", "vertex/s")
        SCRY_RESULT_DESC("PrimitiveRate", "prim/s")
        SCRY_RESULT_DESC("FillRate", "pixel/s")
    SCRY_END_RESULT_DESCS()

    static void bind();

    GeometryTest(const char* name, GeometryPtr geo)
    : Test(name) {
        SCRY_ASSERT(geo);
        _geometry = geo;
    }

    void   setBatchSize(size_t size) { _batchSize = size; }
    size_t getBatchSize() const      { return _batchSize; }

    void setProperty(const std::string& name, size_t value) {
        if (name == "BatchSize") {
            setBatchSize(value);
        } else {
            SCRY_ASSERT(false && "Invalid Property Name");
        }
    }

protected:
    GeometryPtr getGeometry() const {
        return _geometry;
    }

    size_t getVertexCount() const {
        switch (_geometry->getPrimitiveType()) {
            case GL_POINTS:         return getBatchSize() * 1; 
            case GL_LINES:          return getBatchSize() * 2;
            case GL_LINE_STRIP:     return getBatchSize() + 1;
            case GL_LINE_LOOP:      return getBatchSize();
            case GL_TRIANGLES:      return getBatchSize() * 3;
            case GL_TRIANGLE_STRIP: return getBatchSize() + 2;
            case GL_TRIANGLE_FAN:   return getBatchSize() + 2;
            case GL_QUADS:          return getBatchSize() * 4;
            case GL_QUAD_STRIP:     return getBatchSize() * 2 + 2;
            case GL_POLYGON:        return getBatchSize();
            default:                return 0;
        }
    }

private:
    Inited<size_t, 4096> _batchSize;

    GeometryPtr _geometry;
};
SCRY_REF_PTR(GeometryTest);

SCRY_END_NAMESPACE


#endif
