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
#ifndef SCRY_GEOMETRY_TEST_H
#define SCRY_GEOMETRY_TEST_H


#include "Geometry.h"
#include "Test.h"


namespace scry {

    class GeometryTest : public Test {
    protected:
        ~GeometryTest() { }

    public:
        SCRY_BEGIN_RESULT_DESCS()
            SCRY_RESULT_DESC("VertexRate", "vertex/s")
            SCRY_RESULT_DESC("PrimitiveRate", "prim/s")
            SCRY_RESULT_DESC("FillRate", "pixel/s")
            SCRY_RESULT_DESC("BatchRate", "batch/s")
        SCRY_END_RESULT_DESCS()

        static void bind();

        GeometryTest(const char* name, GeometryPtr geo)
        : Test(name) {
            SCRY_ASSERT(geo);
            _geometry = geo;
        }

        void   setBatchSize(size_t size) { _batchSize = size; }
        size_t getBatchSize() const      { return _batchSize; }

        void setup();

    protected:
        struct Buffer {
                  void* data_ptr()       { return &data[0]; }
            const void* data_ptr() const { return &data[0]; }

            std::vector<GLubyte> data;
            Zeroed<Pump> pump;
            Zeroed<GLsizei> stride;
        };

        class BufferIterator {
        public:
            BufferIterator(const Buffer& buffer) {
                _pump = buffer.pump;
                _data = &buffer.data[0];
            }

            void step() {
                if (_pump) {
                    _data = _pump(_data);
                }
            }
        private:
            Pump _pump;
            const void* _data;
        };

        GeometryPtr getGeometry() const {
            return _geometry;
        }

        size_t getVertexCountPerBatch() const;

        size_t getVertexArraySize() {
            if (getGeometry()->indices) {
                return _vertexArraySize;
            } else {
                return getVertexCountPerBatch();
            }
        }

        Uint64 getScreenCoverage() const {
            return _screenCoverage;
        }

        const Buffer& getVertices()  const { return _vertices;  }
        const Buffer& getColors()    const { return _colors;    }
        const Buffer& getNormals()   const { return _normals;   }
        const Buffer& getTexCoords() const { return _texcoords; }
        const Buffer& getIndices()   const { return _indices;   }

    private:
        static void defineBuffer(
            Buffer& buffer, ArrayPtr array, size_t vertexCount,
            const char* name, PumpGetter getter);

        Inited<size_t, 4096> _batchSize;
        Zeroed<Uint64> _screenCoverage;

        /// Size of vertex arrays when using indexed geometry.
        Zeroed<size_t> _vertexArraySize;  // In 'datatype's

        GeometryPtr _geometry;

        Buffer _vertices;
        Buffer _colors;
        Buffer _normals;
        Buffer _texcoords;
        Buffer _indices;
    };
    SCRY_REF_PTR(GeometryTest);

}


#endif
