#include "Action.h"
#include "OpenGL.h"
using namespace boost::python;


namespace scry {
    void Action::bind() {
        class_<Action, ActionPtr, boost::noncopyable>("Action", no_init);
    }

    void ClearAction::bind() {
        class_<ClearAction, ClearActionPtr, bases<Action>, boost::noncopyable>
            ("ClearAction", no_init)
            .def(init<GLbitfield>())
            ;
        implicitly_convertible<ClearActionPtr, ActionPtr>();
    }

    void FlushAction::bind() {
        class_<FlushAction, FlushActionPtr, bases<Action>, boost::noncopyable>
            ("FlushAction", no_init)
            .def(init<>())
            ;
        implicitly_convertible<FlushActionPtr, ActionPtr>();
    }

    void FinishAction::bind() {
        class_<FinishAction, FinishActionPtr, bases<Action>, boost::noncopyable>
            ("FinishAction", no_init)
            .def(init<>())
            ;
        implicitly_convertible<FinishActionPtr, ActionPtr>();
    }

}
