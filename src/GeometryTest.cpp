#include <algorithm>
#include "Context.h"
#include "Coverage.h"
#include "GeometryTest.h"
using namespace boost::python;


namespace scry {

    void GeometryTest::bind() {
        typedef GeometryTest C;
        class_<C, GeometryTestPtr, bases<Test>, boost::noncopyable>
            ("GeometryTest", no_init)
            .add_property("batchSize", &C::getBatchSize, &C::setBatchSize)
            ;

        implicitly_convertible<GeometryTestPtr, TestPtr>();
    }
    
    void GeometryTest::setup() {
        _screenCoverage  = 0;
        _vertexArraySize = 0;
        _vertices  = Buffer();
        _colors    = Buffer();
        _normals   = Buffer();
        _texcoords = Buffer();

        GeometryPtr geometry = getGeometry();

        if (ArrayPtr i = geometry->indices) {
            defineBuffer(_indices, i, getVertexCountPerBatch(), "indices", getIndexPump);

            // Calculate the largest index value and use that+1 as the vertex array size.
            for (size_t j = 0; j < getVertexCountPerBatch(); ++j) {
                size_t value = i->getUInt(_indices.data_ptr(), j);
                _vertexArraySize = std::max<size_t>(_vertexArraySize, value);
            }
            ++_vertexArraySize;
        }

        if (ArrayPtr v = geometry->vertices) {
            defineBuffer(_vertices, v, getVertexArraySize(), "vertices", getVertexPump);

            // @todo: THIS IS WRONG WHEN USING INDEXED GEOMETRY
            _screenCoverage = calculateCoverage(
                geometry->getPrimitiveType(),
                v->getTypeConstant(),
                v->getSize(),
                getVertexArraySize(),
                _vertices.data_ptr());
        }

        defineBuffer(_colors,    geometry->colors,    getVertexArraySize(), "colors",    getColorPump);
        defineBuffer(_normals,   geometry->normals,   getVertexArraySize(), "normals",   getNormalPump);
        defineBuffer(_texcoords, geometry->texcoords, getVertexArraySize(), "texcoords", getTexCoordPump);
    }


    size_t GeometryTest::getVertexCountPerBatch() const {
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


    void GeometryTest::defineBuffer(
        Buffer& buffer,
        ArrayPtr array,
        size_t vertexCount,
        const char* name,
        PumpGetter getter
    ) {
        if (!array) {
            return;
        }

        buffer.data.resize(vertexCount * array->getSize() *
                           array->getTypeSize());
        array->build(buffer.data_ptr(), vertexCount);

        buffer.pump = getter(array->getTypeConstant(), array->getSize());
        if (!buffer.pump) {
            std::cout << "Warning: " << name
                      << " specified but no pump found." << std::endl;
        }
    }

}
