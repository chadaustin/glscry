#ifndef SCRY_TEST_H
#define SCRY_TEST_H


#include <string>
#include <vector>
#include "Action.h"
#include "RefCounted.h"
#include "StateSet.h"
#include "Timer.h"
#include "Types.h"


#define SCRY_DEFINE_TEST_NAME(name)             \
    static const char* getClassName() {         \
        return name;                            \
    }

#define SCRY_BEGIN_RESULT_DESCS()                                       \
    static ResultDescList getClassResultDescs() {                       \
        ResultDescList rv;                                              \

#define SCRY_RESULT_DESC(name, units)           \
    rv.push_back(ResultDesc((name), (units)));

#define SCRY_END_RESULT_DESCS()                                   \
        return rv;                                                \
    }                                                             \
    ResultDescList getResultDescs() {                             \
        return getClassResultDescs();                             \
    }


namespace scry {

    struct ResultDesc {
        ResultDesc(const std::string& name_, const std::string units_)
        : name(name_)
        , units(units_) {
        }

        bool operator==(const ResultDesc& rhs) const {
            return name == rhs.name && units == rhs.units;
        }

        std::string name;
        std::string units;
    };

    typedef std::vector<ResultDesc> ResultDescList;


    typedef std::vector<double> ResultSet;

    inline void normalize(ResultSet& results, double time) {
        for (size_t i = 0; i < results.size(); ++i) {
            results[i] /= time;
        }
    }


    class Test : public RefCounted {
    protected:
        ~Test() { }

    public:
        static void bind();

        // Public interface.

        Test(const char* name) {
            _name = name;
        }

        const char* getName() const {
            return _name.c_str();
        }

        StateSet& getStateSet() {
            return _stateSet;
        }

        void setState(State* state) {
            getStateSet().setState(state);
        }

        void setTransform(
            const Vec4f& row1,
            const Vec4f& row2,
            const Vec4f& row3,
            const Vec4f& row4
        ) {
            _transform.set(
                row1[0], row1[1], row1[2], row1[3],
                row2[0], row2[1], row2[2], row2[3],
                row3[0], row3[1], row3[2], row3[3],
                row4[0], row4[1], row4[2], row4[3]);
        }

        const Matrix44f& getTransform() const {
            return _transform;
        }
            

        void addAction(ActionPtr action) {
            _actionList.push_back(action);
        }

        ResultSet run(float runFor);
    

        // Overridden methods.

        virtual bool isSupported() const { return true; }
        virtual ResultDescList getResultDescs() = 0;
        virtual void setProperty(const std::string& name, size_t value) { }

        virtual void setup()    { }
        virtual void iterate(ResultSet& results) = 0;
        virtual void teardown() { }

    private:
        std::string _name;
        Matrix44f _transform;
        StateSet _stateSet;
        std::vector<ActionPtr> _actionList;
    };
    SCRY_REF_PTR(Test);


}


#endif
