#ifndef SCRY_IMMEDIATE_TEST_H
#define SCRY_IMMEDIATE_TEST_H


#include "GeometryTest.h"
#include "GLUtility.h"


SCRY_BEGIN_NAMESPACE


class ImmediateTest : public GeometryTest {
protected:
    ~ImmediateTest() { }

public:
    static void bind();

    ImmediateTest(const char* name, GeometryPtr geo)
    : GeometryTest(name, geo) {
    }

    void iterate(ResultSet& results) {
        GeometryPtr geometry = getGeometry();

        const void* v_data = getVertexBuffer();
        Pump v_pump = getVertexPump();

        const void* c_data = getColorBuffer();
        Pump c_pump = getColorPump();

        glBegin(geometry->getPrimitiveType());
        for (size_t i = 0; i < getVertexCount(); ++i) {
            if (v_pump) v_data = v_pump(v_data);
            if (c_pump) c_data = c_pump(c_data);
        }
        glEnd();
        
        results[0] += getVertexCount();
        results[1] += getBatchSize();
        results[2] += getScreenCoverage();
    }
};
SCRY_REF_PTR(ImmediateTest);

SCRY_END_NAMESPACE

#endif
