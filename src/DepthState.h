#ifndef SCRY_DEPTH_STATE_H
#define SCRY_DEPTH_STATE_H


#include "OpenGL.h"
#include "State.h"


namespace scry {

    class DepthState : public State {
    protected:
        ~DepthState() { }

    public:
        static void bind();

        void apply() {
            glEnable(GL_DEPTH_TEST);
        }

        void reset() {
            glDisable(GL_DEPTH_TEST);
        }
    };
    SCRY_REF_PTR(DepthState);

}


#endif
