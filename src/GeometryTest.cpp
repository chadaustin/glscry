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
        _vertexPump = 0;
        _colorPump = 0;
        _normalPump = 0;

        GeometryPtr geometry = getGeometry();

        if (ArrayPtr v = geometry->vertices) {
            _vertexBuffer.resize(getVertexCount() * v->getSize() *
                                 v->getTypeSize());
            v->build(&_vertexBuffer[0], getVertexCount());

            _vertexPump = scry::getVertexPump(
                v->getTypeConstant(), v->getSize());
            if (!_vertexPump) {
                std::cout << "Warning: vertices specified but no pump found." << std::endl;
            }

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
            if (!_colorPump) {
                std::cout << "Warning: colors specified but no pump found." << std::endl;
            }
        }

        if (ArrayPtr n = geometry->normals) {
            _normalBuffer.resize(getVertexCount() * n->getSize() *
                                 n->getTypeSize());
            n->build(&_normalBuffer[0], getVertexCount());

            _normalPump = scry::getColorPump(
                n->getTypeConstant(), n->getSize());
            if (!_normalPump) {
                std::cout << "Warning: normals specified but no pump found." << std::endl;
            }
        }
    }

}
