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

        const void* v_data = getVertexBuffer();
        Pump v_pump = getVertexPump();

        const void* c_data = getColorBuffer();
        Pump c_pump = getColorPump();

        const void* n_data = getNormalBuffer();
        Pump n_pump = getNormalPump();

        glBegin(geometry->getPrimitiveType());
        for (size_t i = 0; i < getVertexCount(); ++i) {
            if (v_pump) v_data = v_pump(v_data);
            if (c_pump) c_data = c_pump(c_data);
            if (n_pump) n_data = n_pump(n_data);
        }
        glEnd();
        
        results[0] += getVertexCount();
        results[1] += getBatchSize();
        results[2] += getScreenCoverage();
    }

}
