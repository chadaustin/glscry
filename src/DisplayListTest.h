#ifndef SCRY_DISPLAY_LIST_TEST_H
#define SCRY_DISPLAY_LIST_TEST_H


#include "GeometryTest.h"
#include "GLUtility.h"


SCRY_BEGIN_NAMESPACE

class DisplayListTest : public GeometryTest {
protected:
    ~DisplayListTest() { }

public:
    static void bind();

    DisplayListTest(const char* name, GeometryPtr geo)
    : GeometryTest(name, geo) {
    }

    const char* name() const {
        return "Display List";
    }

    void setup() {
        GeometryTest::setup();

        GeometryPtr geo = getGeometry();

        _list = glGenLists(1);
        glNewList(_list, GL_COMPILE);

        Pump        v_pump = getVertexPump();
        const void* v_data = getVertexBuffer();

        Pump        c_pump = getColorPump();
        const void* c_data = getColorBuffer();

        glBegin(geo->getPrimitiveType());
        for (size_t i = 0; i < getVertexCount(); ++i) {
            if (v_pump) v_data = v_pump(v_data);
            if (c_pump) c_data = c_pump(c_data);
        }
        glEnd();

        glEndList();
    }

    void iterate(ResultSet& results) {
        glCallList(_list);
        results[0] += getVertexCount();
        results[1] += getBatchSize();
        results[2] += getScreenCoverage();
    }

    void teardown() {
        glDeleteLists(_list, 1);
    }

private:
    GLuint _list;
};
SCRY_REF_PTR(DisplayListTest);


SCRY_END_NAMESPACE


#endif
