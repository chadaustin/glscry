#ifndef SCRY_IMMEDIATE_TEST_H
#define SCRY_IMMEDIATE_TEST_H


#include "GeometryTest.h"
#include "GLUtility.h"


namespace scry {

    class ImmediateTest : public GeometryTest {
    protected:
        ~ImmediateTest() { }

    public:
        static void bind();

        ImmediateTest(const char* name, GeometryPtr geo)
        : GeometryTest(name, geo) {
        }

        void iterate(ResultSet& results);
    };
    SCRY_REF_PTR(ImmediateTest);

}


#endif
