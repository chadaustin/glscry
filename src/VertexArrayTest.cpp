#include "VertexArrayTest.h"
using namespace boost::python;


namespace scry {

    void VertexArrayTest::bind() {
        class_<VertexArrayTest, VertexArrayTestPtr, bases<GeometryTest>,
            boost::noncopyable>("VertexArrayTest", no_init)
            .def(init<const char*, GeometryPtr>());

        implicitly_convertible<VertexArrayTestPtr, GeometryTestPtr>();
    }

    void VertexArrayTest::setup() {
        GeometryPtr geometry = getGeometry();

        _vertexCount = getVertexCount();

        if (ArrayPtr v = geometry->vertices) {
            glEnableClientState(GL_VERTEX_ARRAY);

            _vertexBuffer.resize(_vertexCount * v->getSize() *
                                 v->getTypeSize());
            v->build(&_vertexBuffer[0], _vertexCount);
           
            glVertexPointer(v->getSize(), v->getTypeConstant(),
                            0, &_vertexBuffer[0]);
        }
    }

    void VertexArrayTest::iterate(ResultSet& results) {
        glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
        results[0] += _vertexCount;
    }

    void VertexArrayTest::teardown() {
        glDisableClientState(GL_VERTEX_ARRAY);
    }

}
