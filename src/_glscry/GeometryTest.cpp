/* [Begin Copyright Header]
 *
 * GLScry - OpenGL Performance Analysis Tool
 * Copyright (C) 2004-2005  Iowa State University
 * 
 * This software is licensed under the terms of the GNU Lesser Public
 * License, version 2.1, as published by the Free Software Foundation.
 * See the file COPYRIGHT.txt for details.
 * 
 * Authors:
 *   Chad Austin <aegisk@iastate.edu>
 *   Dirk Reiners <dreiners@iastate.edu>
 *
 * [End Copyright Header] */
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

        // Clear previous buffer data.
        _indices   = Buffer();
        _vertices  = Buffer();
        _colors    = Buffer();
        _normals   = Buffer();
        std::fill(_texcoords.begin(), _texcoords.end(), Buffer());

        GeometryPtr geometry = getGeometry();

        if (ArrayPtr i = geometry->indices) {
            defineBuffer(_indices, i, getVertexCountPerBatch(),
                         "indices", FunctionPumpFactory(getIndexPump));

            // Calculate the largest index value and use that+1 as the
            // vertex array size.
            for (size_t j = 0; j < getVertexCountPerBatch(); ++j) {
                size_t value = i->getUInt(_indices.data_ptr(), j);
                _vertexArraySize = std::max<size_t>(_vertexArraySize, value);
            }
            ++_vertexArraySize;
        }

        if (ArrayPtr v = geometry->vertices) {
            defineBuffer(_vertices, v, getVertexArraySize(),
                         "vertices", FunctionPumpFactory(getVertexPump));

            // @todo: THIS IS WRONG WHEN USING INDEXED GEOMETRY
            _screenCoverage = calculateCoverage(
                geometry->getPrimitiveType(),
                v->getTypeConstant(),
                v->getSize(),
                getVertexArraySize(),
                _vertices.data_ptr());
        }

        defineBuffer(_colors,  geometry->colors,  getVertexArraySize(),
                     "colors",  FunctionPumpFactory(getColorPump));
        defineBuffer(_normals, geometry->normals, getVertexArraySize(),
                     "normals", FunctionPumpFactory(getNormalPump));

        for (size_t i = 0; i < _texcoords.size(); ++i) {
            std::ostringstream os;
            os << "texcoords[" << i << "]";
            defineBuffer(_texcoords[i],
                         geometry->texcoords[i],
                         getVertexArraySize(),
                         os.str().c_str(),
                         TexCoordPumpFactory(GL_TEXTURE0 + i));
        }
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
        const PumpFactory& pumpFactory
    ) {
        if (!array) {
            buffer = Buffer();
            return;
        }

        buffer.array = array;
        buffer.data.resize(vertexCount * array->getSize() *
                           array->getTypeSize());
        array->build(buffer.data_ptr(), vertexCount * array->getSize());

        buffer.pump = pumpFactory.getPump(
            array->getTypeConstant(),
            array->getSize());
        if (!buffer.pump) {
            std::cout << "Warning: " << name
                      << " specified but no pump found." << std::endl;
        }
    }

}
