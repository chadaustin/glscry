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
    static void getClassResultDescs(std::vector<ResultDesc>& descs) {

#define SCRY_RESULT_DESC(name, units)                   \
    descs.push_back(ResultDesc((name), (units)));

#define SCRY_END_RESULT_DESCS()                                 \
    }                                                           \
    void getResultDescs(std::vector<ResultDesc>& descs) {       \
        getClassResultDescs(descs);                             \
    }


namespace scry {

    struct ResultDesc {
        ResultDesc(const std::string& name_, const std::string units_) {
            name  = name_;
            units = units_;
        }

        std::string name;
        std::string units;
    };


    class ResultSet {
    public:
        typedef double T;

        ResultSet(size_t size) {
            _results.resize(size);
        }

        size_t size() const {
            return _results.size();
        }

        T& operator[](size_t i) {
            SCRY_ASSERT(i < size());
            return _results[i];
        }

        const T& operator[](size_t i) const {
            SCRY_ASSERT(i < size());
            return _results[i];
        }

        void normalize(T time) {
            for (size_t i = 0; i < size(); ++i) {
                _results[i] /= time;
            }
        }

    private:
        std::vector<T> _results;
    };


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
        virtual void getResultDescs(std::vector<ResultDesc>& descs) = 0;
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
