#ifndef TRIAGARA_DISPLAY_LIST_TEST_H
#define TRIAGARA_DISPLAY_LIST_TEST_H


#include "GeometryTest.h"


TRIAGARA_BEGIN_NAMESPACE

class DisplayListTest : public GeometryTest {
    GLuint _list;

public:
    DisplayListTest(const GeometryGenerator* gen)
        : GeometryTest(gen)
    {
    }

    const char* name() const {
        return "Display List";
    }

    void setup() {
        const std::vector<Triangle>& buffer = getTriangleBuffer();

        _list = glGenLists(1);
        glNewList(_list, GL_COMPILE);
        glBegin(GL_TRIANGLES);
        for (size_t i = 0; i < buffer.size(); ++i) {
            glVertex(buffer[i].v1);
            glVertex(buffer[i].v2);
            glVertex(buffer[i].v3);
        }
        glEnd();
        glEndList();
    }

    void iterate(ResultSet& results) {
        const std::vector<Triangle>& buffer = getTriangleBuffer();

        glCallList(_list);
        results[0] += buffer.size();
    }

    void teardown() {
        glDeleteLists(_list, 1);
    }
};


TRIAGARA_END_NAMESPACE


#endif
