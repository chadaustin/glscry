#include "DisplayListTest.h"
using namespace boost::python;


namespace scry {

    void DisplayListTest::bind() {
        class_<DisplayListTest, DisplayListTestPtr, bases<GeometryTest>,
            boost::noncopyable>("DisplayListTest", no_init)
            .def(init<const char*, GeometryPtr>());

        implicitly_convertible<DisplayListTestPtr, GeometryTestPtr>();
    }

    void DisplayListTest::setup() {
        GeometryTest::setup();

        GeometryPtr geometry = getGeometry();
        if (ArrayPtr i = geometry->indices) {
            if (i->getSize() != 1) {
                throw std::runtime_error("Indices array contains vectors, scalars expected.");
            }

            if (ArrayPtr v = geometry->vertices) {
                glEnableClientState(GL_VERTEX_ARRAY);
                glVertexPointer(v, getVertices().data_ptr());
            }

            if (ArrayPtr c = geometry->colors) {
                glEnableClientState(GL_COLOR_ARRAY);
                glColorPointer(c, getColors().data_ptr());
            }

            if (ArrayPtr n = geometry->normals) {
                glEnableClientState(GL_NORMAL_ARRAY);
                assert(n->getSize() == 3);
                glNormalPointer(n, getNormals().data_ptr());
            }

            if (ArrayPtr t = geometry->texcoords) {
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glTexCoordPointer(t, getTexCoords().data_ptr());
            }
        }

        _list = glGenLists(1);
        glNewList(_list, GL_COMPILE);

        if (geometry->indices) {
            BufferIterator i(getIndices());

            glBegin(geometry->getPrimitiveType());
            for (size_t j = 0; j < getVertexCountPerBatch(); ++j) {
                i.step();
            }
            glEnd();
        } else {
            BufferIterator v(getVertices());
            BufferIterator c(getColors());
            BufferIterator n(getNormals());
            BufferIterator t(getTexCoords());

            glBegin(geometry->getPrimitiveType());
            for (size_t i = 0; i < getVertexCountPerBatch(); ++i) {
                c.step();
                n.step();
                t.step();
                v.step(); // vertices go last.
            }
            glEnd();
        }

        glEndList();
    }

    void DisplayListTest::iterate(ResultSet& results) {
        glCallList(_list);
        results[0] += getVertexCountPerBatch();
        results[1] += getBatchSize();
        results[2] += getScreenCoverage();
        results[3] += 1;
    }

    void DisplayListTest::teardown() {
        glDeleteLists(_list, 1);
    }

}
