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

        BufferIterator v(getVertices());
        BufferIterator c(getColors());
        BufferIterator n(getNormals());
        BufferIterator t(getTexCoords());

        glBegin(geo->getPrimitiveType());
        for (size_t i = 0; i < getVertexCountPerBatch(); ++i) {
            c.step();
            n.step();
            t.step();
            v.step(); // vertices go last.
        }
        glEnd();

        glEndList();
    }

    void DisplayListTest::iterate(ResultSet& results) {
        glCallList(_list);
        results[0] += getVertexCountPerBatch();
        results[1] += getBatchSize();
        results[2] += getScreenCoverage();
    }

    void DisplayListTest::teardown() {
        glDeleteLists(_list, 1);
    }

}
