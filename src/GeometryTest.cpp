#include "GeometryTest.h"
using namespace boost::python;


namespace scry {

    void GeometryTest::bind() {
        class_<GeometryTest, GeometryTestPtr, bases<Test>, boost::noncopyable>
            ("GeometryTest", no_init);

        implicitly_convertible<GeometryTestPtr, TestPtr>();
    }

    void GeometryTest::setup() {
        _screenCoverage = 0;
        _vertices  = Buffer();
        _colors    = Buffer();
        _normals   = Buffer();
        _texcoords = Buffer();

        GeometryPtr geometry = getGeometry();

        if (ArrayPtr v = geometry->vertices) {
            defineBuffer(v, _vertices, "vertices");

            _screenCoverage = calculateCoverage(
                geometry->getPrimitiveType(),
                v->getTypeConstant(),
                v->getSize(),
                getVertexCount(),
                _vertices.data_ptr());
        }

        defineBuffer(geometry->colors,    _colors,    "colors");
        defineBuffer(geometry->normals,   _normals,   "normals");
        defineBuffer(geometry->texcoords, _texcoords, "texcoords");
    }


    void GeometryTest::defineBuffer(ArrayPtr array, Buffer& buffer,
                                    const char* name
    ) {
        if (!array) {
            return;
        }

        buffer.data.resize(getVertexCount() * array->getSize() *
                           array->getTypeSize());
        array->build(buffer.data_ptr(), getVertexCount());

        buffer.pump = scry::getVertexPump(
            array->getTypeConstant(), array->getSize());
        if (!buffer.pump) {
            std::cout << "Warning: " << name
                      << " specified but no pump found." << std::endl;
        }
    }

}
