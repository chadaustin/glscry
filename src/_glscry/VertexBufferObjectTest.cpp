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
#include "VertexBufferObjectTest.h"
using namespace boost::python;


namespace scry {

    inline const void* asBufferOffset(size_t i) {
        static GLubyte const* const null = 0;
        return null + i;
    }

    void VertexBufferObjectTest::bind() {
        scope s = class_<VertexBufferObjectTest, VertexBufferObjectTestPtr,
                         bases<GeometryTest>, boost::noncopyable>
            ("VertexBufferObjectTest", no_init)
            .def(init<const char*, GeometryPtr>())
            .def("setBufferType", &VertexBufferObjectTest::setBufferType)
            .def("setStorageMode", &VertexBufferObjectTest::setStorageMode)
            ;

        enum_<StorageMode>("StorageMode")
            .value("SEPARATE_BUFFERS",       SEPARATE_BUFFERS)
            .value("ONE_BUFFER",             ONE_BUFFER)
            .value("ONE_BUFFER_INTERLEAVED", ONE_BUFFER_INTERLEAVED)
            ;

        implicitly_convertible<VertexBufferObjectTestPtr, GeometryTestPtr>();
    }

    void VertexBufferObjectTest::setup() {
        GeometryTest::setup();

        GeometryPtr geometry = getGeometry();

        // The index buffer gets to be handled separately.
        if (ArrayPtr i = geometry->indices) {
            _buffers.push_back(createVBO(getIndices(),
                                         GL_ELEMENT_ARRAY_BUFFER_ARB));
        }

        switch (_storageMode.get()) {
            case SEPARATE_BUFFERS: {
                if (ArrayPtr v = geometry->vertices) {
                    _buffers.push_back(createVBO(getVertices()));

                    glEnableClientState(GL_VERTEX_ARRAY);
                    glVertexPointer(v->getSize(), v->getTypeConstant(), 0, 0);
                }

                if (ArrayPtr c = geometry->colors) {
                    _buffers.push_back(createVBO(getColors()));

                    glEnableClientState(GL_COLOR_ARRAY);
                    glColorPointer(c->getSize(), c->getTypeConstant(), 0, 0);
                }

                if (ArrayPtr n = geometry->normals) {
                    _buffers.push_back(createVBO(getNormals()));

                    glEnableClientState(GL_NORMAL_ARRAY);
                    assert(n->getSize() == 3);
                    glNormalPointer(n->getTypeConstant(), 0, 0);
                }

                if (ArrayPtr t = geometry->texcoords) {
                    _buffers.push_back(createVBO(getTexCoords()));

                    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                    glTexCoordPointer(t->getSize(), t->getTypeConstant(),
                                      0, 0);
                }
            } break;

            case ONE_BUFFER: {
                const size_t totalSize =
                    getVertices().data.size() +
                    getColors().data.size() +
                    getNormals().data.size() +
                    getTexCoords().data.size();
                std::vector<GLubyte> buffer(totalSize);
                GLubyte* start = &buffer[0];
                GLubyte* out = start;

                if (ArrayPtr v = geometry->vertices) {
                    memcpy(out, getVertices().data_ptr(),
                           getVertices().data.size());
                    out += getVertices().data.size();
                }

                if (ArrayPtr c = geometry->colors) {
                    memcpy(out, getColors().data_ptr(),
                           getColors().data.size());
                    out += getColors().data.size();
                }

                if (ArrayPtr n = geometry->normals) {
                    memcpy(out, getNormals().data_ptr(),
                           getNormals().data.size());
                    out += getNormals().data.size();
                }

                if (ArrayPtr t = geometry->texcoords) {
                    memcpy(out, getTexCoords().data_ptr(),
                           getTexCoords().data.size());
                    out += getTexCoords().data.size();
                }

                SCRY_ASSERT(out == start + totalSize &&
                            "We didn't write the same amount of data we "
                            "thought we would.");
                GLuint handle;
                glGenBuffersARB(1, &handle);
                glBindBufferARB(GL_ARRAY_BUFFER_ARB, handle);
                glBufferDataARB(GL_ARRAY_BUFFER_ARB, totalSize, start,
                                _bufferType);
                _buffers.push_back(handle);

                out = start;
                if (ArrayPtr v = geometry->vertices) {
                    glEnableClientState(GL_VERTEX_ARRAY);
                    glVertexPointer(v->getSize(), v->getTypeConstant(), 0,
                                    asBufferOffset(out - start));
                    out += getVertices().data.size();
                }

                if (ArrayPtr c = geometry->colors) {
                    glEnableClientState(GL_COLOR_ARRAY);
                    glColorPointer(c->getSize(), c->getTypeConstant(), 0,
                                   asBufferOffset(out - start));
                    out += getColors().data.size();
                }

                if (ArrayPtr n = geometry->normals) {
                    glEnableClientState(GL_NORMAL_ARRAY);
                    assert(n->getSize() == 3);
                    glNormalPointer(n->getTypeConstant(), 0,
                                    asBufferOffset(out - start));
                    out += getNormals().data.size();
                }

                if (ArrayPtr t = geometry->texcoords) {
                    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                    glTexCoordPointer(t->getSize(), t->getTypeConstant(), 0,
                                      asBufferOffset(out - start));
                    out += getTexCoords().data.size();
                }
            } break;

            case ONE_BUFFER_INTERLEAVED: {
                const size_t totalSize =
                    getVertices().data.size() +
                    getColors().data.size() +
                    getNormals().data.size() +
                    getTexCoords().data.size();
                const size_t totalStride =
                    getStride(geometry->vertices) +
                    getStride(geometry->colors) +
                    getStride(geometry->normals) +
                    getStride(geometry->texcoords);

                SCRY_ASSERT(totalStride * getVertexArraySize() == totalSize &&
                            "Incorrect buffer size or stride.");

                std::vector<GLubyte> buffer(totalSize);
                GLubyte* start = &buffer[0];
                GLubyte* out = start;

                if (ArrayPtr v = geometry->vertices) {
                    size_t stride = getStride(v);
                    const GLubyte* write = &(getVertices().data)[0];
                    for (size_t i = 0; i < getVertexArraySize(); ++i) {
                        memcpy(out + totalStride * i, write + stride * i,
                               stride);
                    }
                    out += stride;
                }

                if (ArrayPtr c = geometry->colors) {
                    size_t stride = getStride(c);
                    const GLubyte* write = &(getColors().data)[0];
                    for (size_t i = 0; i < getVertexArraySize(); ++i) {
                        memcpy(out + totalStride * i, write + stride * i,
                               stride);
                    }
                    out += stride;
                }

                if (ArrayPtr n = geometry->normals) {
                    size_t stride = getStride(n);
                    const GLubyte* write = &(getNormals().data)[0];
                    for (size_t i = 0; i < getVertexArraySize(); ++i) {
                        memcpy(out + totalStride * i, write + stride * i,
                               stride);
                    }
                    out += stride;
                }

                if (ArrayPtr t = geometry->texcoords) {
                    size_t stride = getStride(t);
                    const GLubyte* write = &(getTexCoords().data)[0];
                    for (size_t i = 0; i < getVertexArraySize(); ++i) {
                        memcpy(out + totalStride * i, write + stride * i,
                               stride);
                    }
                    out += stride;
                }

                SCRY_ASSERT(out == start + totalStride &&
                            "We didn't write the same amount of data we "
                            "thought we would.");
                GLuint handle;
                glGenBuffersARB(1, &handle);
                glBindBufferARB(GL_ARRAY_BUFFER_ARB, handle);
                glBufferDataARB(GL_ARRAY_BUFFER_ARB, totalSize, start,
                                _bufferType);
                _buffers.push_back(handle);

                size_t stride = 0;
                if (ArrayPtr v = geometry->vertices) {
                    glEnableClientState(GL_VERTEX_ARRAY);
                    glVertexPointer(v->getSize(), v->getTypeConstant(),
                                    totalStride, asBufferOffset(stride));
                    stride += getStride(v);
                }

                if (ArrayPtr c = geometry->colors) {
                    glEnableClientState(GL_COLOR_ARRAY);
                    glColorPointer(c->getSize(), c->getTypeConstant(),
                                   totalStride, asBufferOffset(stride));
                    stride += getStride(c);
                }

                if (ArrayPtr n = geometry->normals) {
                    glEnableClientState(GL_NORMAL_ARRAY);
                    assert(n->getSize() == 3);
                    glNormalPointer(n->getTypeConstant(), totalStride,
                                    asBufferOffset(stride));
                    stride += getStride(n);
                }

                if (ArrayPtr t = geometry->texcoords) {
                    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                    glTexCoordPointer(t->getSize(), t->getTypeConstant(),
                                      totalStride, asBufferOffset(stride));
                    stride += getStride(t);
                }

            } break;

            default: {
                SCRY_ASSERT(false && "Invalid storageMode");
            } break;
        }
    }

    void VertexBufferObjectTest::iterate(ResultValues& results) {
        GeometryPtr geo = getGeometry();

        // In indexing support, use glDrawRangeElements or glDrawElements.
        if (ArrayPtr i = geo->indices) {
            glDrawElements(geo->getPrimitiveType(),
                           getVertexCountPerBatch(),
                           i->getTypeConstant(),
                           0);
        } else {
            glDrawArrays(geo->getPrimitiveType(), 0, getVertexCountPerBatch());
        }
        results[0] += getVertexCountPerBatch();
        results[1] += getBatchSize();
        results[2] += getScreenCoverage();
        results[3] += 1;
    }

    void VertexBufferObjectTest::teardown() {
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
        for (size_t i = 0; i < _buffers.size(); ++i) {
            glDeleteBuffersARB(1, &_buffers[i]);
        }
        _buffers.clear();
    }

    GLuint VertexBufferObjectTest::createVBO(
        const Buffer& buffer, GLenum target
    ) {
        GLuint handle;
        glGenBuffersARB(1, &handle);
        glBindBufferARB(target, handle);
        glBufferDataARB(
            target,
            buffer.data.size(),
            buffer.data_ptr(),
            _bufferType);
        return handle;
    }

    GLsizei VertexBufferObjectTest::getStride(ArrayPtr array) {
        if (array) {
            return array->getSize() * array->getTypeSize();
        } else {
            return 0;
        }
    }

}
