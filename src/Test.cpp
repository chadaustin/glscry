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
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "Context.h"
#include "GLUtility.h"
#include "Test.h"
using namespace boost;
using namespace boost::python;


namespace scry {

    // Handles calling teardown() on exit in an exception-safe way.
    class RunSentry {
        Test* _test;
    public:
        RunSentry(Test* test): _test(test) {
            glPushMatrix();
            glLoadMatrixf(_test->getTransform().getData());
            _test->setup();
        }
        ~RunSentry() {
            try {
                _test->teardown();
            }
            catch (const std::exception& /*e*/) {
                // nothing
            }

            glPopMatrix();
        }
    };


    void Test::bind() {
        class_<ResultDesc>("ResultDesc", no_init)
            .def_readonly("name",  &ResultDesc::name)
            .def_readonly("units", &ResultDesc::units)
            .def(self == self)
            .def(self < self)
            ;

        class_<ResultDescList>("ResultDescList")
            .def(vector_indexing_suite<ResultDescList>())
            ;

        class_<ResultSet>("ResultSet")
            .def(vector_indexing_suite<ResultSet>())
            .def("normalize", &normalize)
            ;

        typedef Test C;
        class_<C, TestPtr, noncopyable>("Test", no_init)
            .add_property("name",  &C::getName)
            .def("setTransform",   &C::setTransform)
            .add_property("fullStateSwitch",
                          &C::getFullStateSwitch, &C::setFullStateSwitch)
            .def("addStateSet",    &C::addStateSet)
            .def("addAction",      &C::addAction)
            .def("run",            &C::run)
            .def("isSupported",    &C::isSupported)
            .def("getResultDescs", &C::getResultDescs)
            ;
    }


    ResultSet Test::run(float runFor) {
        // Handles calling teardown() on exit in an exception-safe way.
        RunSentry sentry__(this);

        ResultDescList descs = getResultDescs();
        ResultSet results(descs.size());

        size_t currentStateSet = 0;

        checkOpenGLErrors();

        // Don't time setup and teardown.
        glFinish();

        Timer timer;
        while (timer.elapsed() < runFor) {
            for (size_t i = 0; i < _actionList.size(); ++i) {
                _actionList[i]->execute();
            }

            //checkOpenGLErrors();

            if (!_stateSetList.empty()) {
                setCurrentStateSet(_stateSetList[currentStateSet],
                                   _fullStateSwitch);
                currentStateSet = (currentStateSet + 1) % _stateSetList.size();
            } else {
                setCurrentStateSet(0, _fullStateSwitch);
            }

            //checkOpenGLErrors();

            iterate(results);

            checkOpenGLErrors();
        }
        glFinish();

        // timer.elapsed() is evaluated before RunSentry is destroyed.
        normalize(results, timer.elapsed());

        pumpMessages();
        return results;
    }

}

