#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "Context.h"
#include "Test.h"
using namespace boost;
using namespace boost::python;


namespace scry {

    // Handles calling teardown() on exit in an exception-safe way.
    class RunSentry {
        Test* _test;
    public:
        RunSentry(Test* test): _test(test) {
            _test->getStateSet().apply();
            glPushMatrix();
            glLoadMatrixf(_test->getTransform().getData());
            _test->setup();
        }
        ~RunSentry() {
            try {
                _test->teardown();
                glPopMatrix();
                _test->getStateSet().reset();
            }
            catch (const std::exception& /*e*/) {
                // nothing
            }
        }
    };


    void Test::bind() {
        class_<ResultDesc>("ResultDesc", no_init)
            .def_readonly("name",  &ResultDesc::name)
            .def_readonly("units", &ResultDesc::units)
            ;

        class_<ResultDescList>("ResultDescList")
            .def(vector_indexing_suite<ResultDescList>())
            ;

        class_<ResultSet>("ResultSet", no_init)
            .def(vector_indexing_suite<ResultSet>())
            .def("normalize", &normalize)
            ;

        typedef Test C;
        class_<C, TestPtr, noncopyable>("Test", no_init)
            .def("getName",        &C::getName)
            .def("setState",       &C::setState)
            .def("setTransform",   &C::setTransform)
            .def("addAction",      &C::addAction)
            .def("run",            &C::run)
            .def("isSupported",    &C::isSupported)
            .def("getResultDescs", &C::getResultDescs)
            .def("setProperty",    &C::setProperty)
            ;
    }


    ResultSet Test::run(float runFor) {
        // Handles calling teardown() on exit in an exception-safe way.
        RunSentry sentry__(this);

        ResultDescList descs = getResultDescs();
        ResultSet results(descs.size());

        // Don't bother timing setup and teardown.
        glFinish();

        Timer timer;
        while (timer.elapsed() < runFor) {
            for (size_t i = 0; i < _actionList.size(); ++i) {
                _actionList[i]->execute();
            }
            iterate(results);
            pumpMessages();
        }
        glFinish();

        // timer.elapsed() is evaluated before RunSentry is destroyed.
        normalize(results, timer.elapsed());

        return results;
    }

}

