#include "DisplayListTest.h"
using namespace boost::python;


namespace scry {

    void DisplayListTest::bind() {
        class_<DisplayListTest, DisplayListTestPtr, bases<GeometryTest>,
            boost::noncopyable>("DisplayListTest", no_init)
            .def(init<const char*, GeometryPtr>());

        implicitly_convertible<DisplayListTestPtr, GeometryTestPtr>();
    }

    void DisplayListTest::setup() {
        GeometryTest::setup();

        GeometryPtr geo = getGeometry();

        _list = glGenLists(1);
        glNewList(_list, GL_COMPILE);

        Pump        v_pump = getVertexPump();
        const void* v_data = getVertexBuffer();

        Pump        c_pump = getColorPump();
        const void* c_data = getColorBuffer();

        Pump n_pump = getNormalPump();
        const void* n_data = getNormalBuffer();

        glBegin(geo->getPrimitiveType());
        for (size_t i = 0; i < getVertexCount(); ++i) {
            if (v_pump) v_data = v_pump(v_data);
            if (c_pump) c_data = c_pump(c_data);
            if (n_pump) n_data = n_pump(n_data);
        }
        glEnd();

        glEndList();
    }

    void DisplayListTest::iterate(ResultSet& results) {
        glCallList(_list);
        results[0] += getVertexCount();
        results[1] += getBatchSize();
        results[2] += getScreenCoverage();
    }

    void DisplayListTest::teardown() {
        glDeleteLists(_list, 1);
    }

}
