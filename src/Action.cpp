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
            .def(init<>())
            ;
        implicitly_convertible<ClearActionPtr, ActionPtr>();
    }

    void ClearAction::execute() {
        glClear(GL_DEPTH_BUFFER_BIT);
    }
}
