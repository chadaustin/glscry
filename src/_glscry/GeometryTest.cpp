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
            .add_property("geometry", &C::getGeometry)
            ;

        implicitly_convertible<GeometryTestPtr, TestPtr>();
    }

    GeometryTest::GeometryTest(const char* name, GeometryPtr geo)
    : Test(name)
    , _geometry(geo) {
        SCRY_ASSERT(geo);
        _buffers.texcoords.resize(geo->texcoords.size());
    }
    
    void GeometryTest::setup() {
        _screenCoverage  = 0;
        _vertexArraySize = 0;

        // Clear previous buffer data.
        _buffers.indices   = Buffer();
        _buffers.vertices  = Buffer();
        _buffers.colors    = Buffer();
        _buffers.normals   = Buffer();
        std::fill(_buffers.texcoords.begin(), _buffers.texcoords.end(),
                  Buffer());

        GeometryPtr geometry = getGeometry();

        if (ArrayPtr i = geometry->indices) {
            defineBuffer(_buffers.indices, i, getVertexCountPerIteration(),
                         "indices", FunctionPumpFactory(getIndexPump));

            // Calculate the largest index value and use that+1 as the
            // vertex array size.
            for (size_t j = 0; j < getVertexCountPerIteration(); ++j) {
                size_t value = i->getUInt(_buffers.indices.data_ptr(), j);
                _vertexArraySize = std::max<size_t>(_vertexArraySize, value);
            }
            ++_vertexArraySize;
        } else {
            _vertexArraySize = getVertexCountPerIteration();
        }

        if (ArrayPtr v = geometry->vertices) {
            defineBuffer(_buffers.vertices, v, getVertexArraySize(),
                         "vertices", FunctionPumpFactory(getVertexPump));

            // @todo: THIS IS WRONG WHEN USING INDEXED GEOMETRY
            // @todo: It is also wrong when using transform matrices.
            for (size_t i = 0; i < geometry->batches.size(); ++i) {
                _screenCoverage += calculateCoverage(
                    geometry->batches[i].primitiveType,
                    v->getTypeConstant(),
                    v->getVectorSize(),
                    geometry->batches[i].getVertexCount(),
                    _buffers.vertices.data_ptr());
            }
        }

        defineBuffer(_buffers.colors,  geometry->colors,  getVertexArraySize(),
                     "colors",  FunctionPumpFactory(getColorPump));
        defineBuffer(_buffers.normals, geometry->normals, getVertexArraySize(),
                     "normals", FunctionPumpFactory(getNormalPump));

        for (size_t i = 0; i < _buffers.texcoords.size(); ++i) {
            std::ostringstream os;
            os << "texcoords[" << i << "]";
            defineBuffer(_buffers.texcoords[i],
                         geometry->texcoords[i],
                         getVertexArraySize(),
                         os.str().c_str(),
                         TexCoordPumpFactory(GL_TEXTURE0 + i));
        }


        _vertexDataSize = 0;
        _vertexDataSize += getArrayVectorSize(geometry->vertices);
        _vertexDataSize += getArrayVectorSize(geometry->colors);
        _vertexDataSize += getArrayVectorSize(geometry->normals);
        for (size_t ti = 0; ti < geometry->texcoords.size(); ++ti) {
            _vertexDataSize += getArrayVectorSize(geometry->texcoords[ti]);
        }
    }


    void GeometryTest::fillBufferIteratorList(BufferIteratorList& bi) const {
        tryAddBuffer(bi, getColors());
        tryAddBuffer(bi, getNormals());
        for (size_t i = 0; i < getTexCoordsCount(); ++i) {
            tryAddBuffer(bi, getTexCoords(i));
        }
        // Vertices go last.
        tryAddBuffer(bi, getVertices());
    }


    void GeometryTest::enableArrays() const {
        GeometryPtr geometry = getGeometry();

        if (ArrayPtr v = geometry->vertices) {
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(v, getVertices().data_ptr());
        }

        if (ArrayPtr c = geometry->colors) {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(c, getColors().data_ptr());
        }

        if (ArrayPtr n = geometry->normals) {
            SCRY_ASSERT(n->getVectorSize() == 3);
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(n, getNormals().data_ptr());
        }

        for (size_t ti = 0; ti < geometry->texcoords.size(); ++ti) {
            if (ArrayPtr t = geometry->texcoords[ti]) {
                if (ti >= 1) {
                    glClientActiveTextureARB(GL_TEXTURE0 + ti);
                }
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glTexCoordPointer(t, getTexCoords(ti).data_ptr());
                if (ti >= 1) {
                    glClientActiveTextureARB(GL_TEXTURE0);
                }
            }
        }
    }


    void GeometryTest::disableArrays() const {
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);

        GeometryPtr geometry = getGeometry();
        for (size_t ti = 0; ti < geometry->texcoords.size(); ++ti) {
            if (ti >= 1) {
                glClientActiveTextureARB(GL_TEXTURE0 + ti);
            }
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            if (ti >= 1) {
                glClientActiveTextureARB(GL_TEXTURE0);
            }
        }
    }


    size_t GeometryTest::getVertexCountPerIteration() const {
        const PrimitiveBatchList& batches = getGeometry()->batches;

        size_t total = 0;
        for (size_t i = 0; i < batches.size(); ++i) {
            total += batches[i].getVertexCount();
        }
        return total;
    }

    size_t GeometryTest::getPrimitiveCountPerIteration() const {
        const PrimitiveBatchList& batches = getGeometry()->batches;

        size_t total = 0;
        for (size_t i = 0; i < batches.size(); ++i) {
            total += batches[i].batchSize;
        }
        return total;       
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
        buffer.data.resize(vertexCount * getArrayVectorSize(array));
        array->build(buffer.data_ptr(), vertexCount * array->getVectorSize());

        buffer.pump = pumpFactory.getPump(
            array->getTypeConstant(),
            array->getVectorSize());
        if (!buffer.pump) {
            std::cout << "Warning: " << name
                      << " specified but no pump found." << std::endl;
        }
    }

}
