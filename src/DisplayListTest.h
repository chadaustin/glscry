#ifndef SCRY_DISPLAY_LIST_TEST_H
#define SCRY_DISPLAY_LIST_TEST_H


#include "GeometryTest.h"
#include "GLUtility.h"


SCRY_BEGIN_NAMESPACE

class DisplayListTest : public GeometryTest {
protected:
    ~DisplayListTest() { }

public:
    static void bind();

    DisplayListTest(const char* name, GeometryPtr geo)
    : GeometryTest(name, geo) {
    }

    void setup();
    void iterate(ResultSet& results);
    void teardown();

private:
    GLuint _list;
};
SCRY_REF_PTR(DisplayListTest);


SCRY_END_NAMESPACE


#endif
