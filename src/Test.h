#ifndef TRIAGARA_TEST_H
#define TRIAGARA_TEST_H


#include <string>
#include "glew.h"
#include "Base.h"
#include "Context.h"
#include "StateSet.h"
#include "Timer.h"


#define TRIAGARA_BEGIN_RESULT_DESCS()                                   \
    static void getClassResultDescs(std::vector<ResultDesc>& descs) {

#define TRIAGARA_RESULT_DESC(name, units)               \
    descs.push_back(ResultDesc((name), (units)));

#define TRIAGARA_END_RESULT_DESCS()                             \
    }                                                           \
    void getResultDescs(std::vector<ResultDesc>& descs) {       \
        getClassResultDescs(descs);                             \
    }


TRIAGARA_BEGIN_NAMESPACE


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
        assert(i < size());
        return _results[i];
    }

    const T& operator[](size_t i) const {
        assert(i < size());
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


class Test;


class Test {
public:
    virtual ~Test() { }

    static void bind();

    // Public interface.

    StateSet& getStateSet() {
        return _stateSet;
    }

    void setState(State* state) {
        getStateSet().setState(state);
    }

    ResultSet run(float runFor);
    

    // Overridden methods.

    virtual const char* name() const = 0;

    virtual bool supported() const { return true; }

    virtual void getResultDescs(std::vector<ResultDesc>& descs) = 0;

    virtual void setProperty(const std::string& name, size_t value) { }

    virtual void setup()    { }
    virtual void iterate(ResultSet& results) = 0;
    virtual void teardown() { }

private:
    StateSet _stateSet;
};

TRIAGARA_END_NAMESPACE


#endif
