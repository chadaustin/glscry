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
            SCRY_RESULT_DESC("VertexRate",    "vertex/s")
            SCRY_RESULT_DESC("PrimitiveRate", "prim/s")
            SCRY_RESULT_DESC("FillRate",      "pixel/s")
            SCRY_RESULT_DESC("BatchRate",     "batch/s")
            SCRY_RESULT_DESC("DataRate",      "byte/s")
        SCRY_END_RESULT_DESCS()

        static void bind();

        GeometryTest(const char* name, GeometryPtr geo)
        : Test(name) {
            SCRY_ASSERT(geo);
            _geometry = geo;
            _texcoords.resize(geo->texcoords.size());
        }

        void   setBatchSize(size_t size) { _batchSize = size; }
        size_t getBatchSize() const      { return _batchSize; }

        void setup();

    protected:
        struct Buffer {
                  GLubyte* data_ptr()       { return &data[0]; }
            const GLubyte* data_ptr() const { return &data[0]; }

            ArrayPtr array;  // The array that filled this buffer.
            std::vector<GLubyte> data;
            Zeroed<Pump> pump;
            Zeroed<GLsizei> stride;
        };

        class BufferIterator {
        public:
            BufferIterator(const Buffer& buffer) {
                _pump = buffer.pump;
                _data = buffer.data_ptr();
            }

            operator bool() const {
                return _pump != Pump();
            }

            void step() {
                _data = _pump(_data);
            }

        private:
            Pump _pump;
            const void* _data;
        };

        typedef std::vector<BufferIterator> BufferIteratorList;

        static void tryAddBuffer(BufferIteratorList& bi, const Buffer& b) {
            BufferIterator i(b);
            if (i) {
                bi.push_back(i);
            }
        }

        void fillBufferIteratorList(BufferIteratorList& bi) const;
        void enableArrays() const;
        void disableArrays() const;

        GeometryPtr getGeometry() const {
            return _geometry;
        }

        size_t getVertexCountPerBatch() const;

        size_t getVertexArraySize() {
            return getGeometry()->indices
                ? size_t(_vertexArraySize)
                : getVertexCountPerBatch();
        }

        size_t getArrayVertexSize(const ArrayPtr& a) {
            return a
                ? a->getSize() * a->getTypeSize()
                : 0;
        }

        size_t getVertexDataSize() {
            return _vertexDataSize;
        }

        Uint64 getScreenCoverage() const {
            return _screenCoverage;
        }

        const Buffer& getIndices()       const { return _indices;   }
        const Buffer& getVertices()      const { return _vertices;  }
        const Buffer& getColors()        const { return _colors;    }
        const Buffer& getNormals()       const { return _normals;   }
        const size_t getTexCoordsCount() const { return _texcoords.size(); }
        const Buffer& getTexCoords(size_t i) const { return _texcoords[i]; }
        
    private:
        static void defineBuffer(
            Buffer& buffer, ArrayPtr array, size_t vertexCount,
            const char* name, const PumpFactory& pumpFactory);

        Inited<size_t, 4096> _batchSize;
        Zeroed<Uint64> _screenCoverage;

        /// Size of vertex arrays when using indexed geometry.
        Zeroed<size_t> _vertexArraySize;  // In 'datatype's

        Zeroed<size_t> _vertexDataSize;

        GeometryPtr _geometry;

        Buffer _indices;
        Buffer _vertices;
        Buffer _colors;
        Buffer _normals;
        std::vector<Buffer> _texcoords;
    };
    SCRY_REF_PTR(GeometryTest);

}


#endif
