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


#include "Buffer.h"
#include "Geometry.h"
#include "Test.h"


namespace scry {

    struct GeometryBuffers {
        Buffer indices;
        Buffer vertices;
        Buffer colors;
        Buffer normals;
        std::vector<Buffer> texcoords;
    };


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

        GeometryTest(const char* name, GeometryPtr geo);
        //GeometryTest(const char* name, std::vector<GeometryPtr> geos);

        size_t getBatchSize() const {
            return getGeometry()->getBatchSize();
        }

        void setBatchSize(size_t size) {
            getGeometry()->setBatchSize(size);
        }

        void setup();

    protected:
        void fillBufferIteratorList(BufferIteratorList& bi) const;
        void enableArrays() const;
        void disableArrays() const;

        GeometryPtr getGeometry() const {
            return _geometry[0];
        }

        size_t getVertexCountPerBatch() const;

        size_t getVertexArraySize(GeometryPtr geo) {
            return geo->indices
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

        const Buffer& getIndices()       const { return _buffers.indices;   }
        const Buffer& getVertices()      const { return _buffers.vertices;  }
        const Buffer& getColors()        const { return _buffers.colors;    }
        const Buffer& getNormals()       const { return _buffers.normals;   }
        const size_t getTexCoordsCount() const { return _buffers.texcoords.size(); }
        const Buffer& getTexCoords(size_t i) const { return _buffers.texcoords[i]; }
        
    private:
        static void defineBuffer(
            Buffer& buffer, ArrayPtr array, size_t vertexCount,
            const char* name, const PumpFactory& pumpFactory);

        Zeroed<Uint64> _screenCoverage;

        /// Size of vertex arrays when using indexed geometry.
        Zeroed<size_t> _vertexArraySize;  // In 'datatype's

        Zeroed<size_t> _vertexDataSize;

        Zeroed<size_t> _currentGeometry;
        std::vector<GeometryPtr> _geometry;

        GeometryBuffers _buffers;

    };
    SCRY_REF_PTR(GeometryTest);

}


#endif
