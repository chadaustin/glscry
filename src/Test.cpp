#include <boost/python.hpp>
#include "Test.h"
using namespace boost;
using namespace boost::python;


SCRY_BEGIN_NAMESPACE


// Handles calling teardown() on exit in an exception-safe way.
class RunSentry {
    Test* _test;
public:
    RunSentry(Test* test): _test(test) {
        _test->getStateSet().apply();
        _test->setup();
    }
    ~RunSentry() {
        try {
            _test->teardown();
            _test->getStateSet().reset();
        }
        catch (const std::exception& /*e*/) {
            // nothing
        }
    }
};


void Test::bind() {
    class_<Test, noncopyable>("Test", no_init);
}


ResultSet Test::run(float runFor) {
    // Handles calling teardown() on exit in an exception-safe way.
    RunSentry sentry__(this);

    std::vector<ResultDesc> descs;
    getResultDescs(descs);
    ResultSet results(descs.size());

    // Don't bother timing setup and teardown.
    glFinish();

    Timer timer;
    while (timer.elapsed() < runFor) {
        iterate(results);
        pumpMessages();
    }
    glFinish();

    // timer.elapsed() is evaluated before RunSentry is destroyed.
    results.normalize(timer.elapsed());

    return results;
}


SCRY_END_NAMESPACE
