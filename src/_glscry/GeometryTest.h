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

        void fillBufferIteratorList(BufferIteratorList& bi) {
            tryAddBuffer(bi, getColors());
            tryAddBuffer(bi, getNormals());
            for (size_t i = 0; i < getTexCoordsCount(); ++i) {
                tryAddBuffer(bi, getTexCoords(i));
            }
            // Vertices go last.
            tryAddBuffer(bi, getVertices());
        }

        void enableArrays() const {
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
                SCRY_ASSERT(n->getSize() == 3);
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

        void disableArrays() const {
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
