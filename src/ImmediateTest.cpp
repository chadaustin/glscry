#include "ImmediateTest.h"
using namespace boost::python;


namespace scry {

    void ImmediateTest::bind() {
        class_<ImmediateTest, ImmediateTestPtr, bases<GeometryTest>,
            boost::noncopyable>("ImmediateTest", no_init)
            .def(init<const char*, GeometryPtr>());

        implicitly_convertible<ImmediateTestPtr, GeometryTestPtr>();
    }

    void ImmediateTest::iterate(ResultSet& results) {
        GeometryPtr geometry = getGeometry();

        BufferIterator v(getVertices());
        BufferIterator c(getColors());
        BufferIterator n(getNormals());
        BufferIterator t(getTexCoords());

        glBegin(geometry->getPrimitiveType());
        for (size_t i = 0; i < getVertexCount(); ++i) {
            c.step();
            n.step();
            t.step();
            v.step(); // vertices go last.
        }
        glEnd();
        
        results[0] += getVertexCount();
        results[1] += getBatchSize();
        results[2] += getScreenCoverage();
    }

}
