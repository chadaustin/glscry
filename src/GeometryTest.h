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

    void setup() {
        _screenCoverage = 0;
        _vertexPump = 0;
        _colorPump = 0;

        GeometryPtr geometry = getGeometry();

        if (ArrayPtr v = geometry->vertices) {
            _vertexBuffer.resize(getVertexCount() * v->getSize() *
                                 v->getTypeSize());
            v->build(&_vertexBuffer[0], getVertexCount());

            _vertexPump = scry::getVertexPump(
                v->getTypeConstant(), v->getSize());

            _screenCoverage = calculateCoverage(
                geometry->getPrimitiveType(),
                v->getTypeConstant(),
                v->getSize(),
                getVertexCount(),
                &_vertexBuffer[0]);
        }

        if (ArrayPtr c = geometry->colors) {
            _colorBuffer.resize(getVertexCount() * c->getSize() *
                                 c->getTypeSize());
            c->build(&_colorBuffer[0], getVertexCount());

            _colorPump = scry::getColorPump(
                c->getTypeConstant(), c->getSize());
        }
    }

    void teardown() {
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

    size_t getScreenCoverage() const {
        return _screenCoverage;
    }

    const void* getVertexBuffer() const { return &_vertexBuffer[0];  }
    Pump getVertexPump()          const { return _vertexPump; }

    const void* getColorBuffer() const { return &_colorBuffer[0]; }
    Pump getColorPump()          const { return _colorPump; }

private:
    Inited<size_t, 4096> _batchSize;
    Zeroed<size_t> _screenCoverage;

    GeometryPtr _geometry;

    std::vector<GLubyte> _vertexBuffer;
    Zeroed<Pump> _vertexPump;

    std::vector<GLubyte> _colorBuffer;
    Zeroed<Pump> _colorPump;
};
SCRY_REF_PTR(GeometryTest);

SCRY_END_NAMESPACE


#endif
