#ifndef SCRY_DEPTH_STATE_H
#define SCRY_DEPTH_STATE_H


#include "State.h"


SCRY_BEGIN_NAMESPACE


class DepthState : public State {
    void apply() {
        glEnable(GL_DEPTH_TEST);
    }

    void reset() {
        glDisable(GL_DEPTH_TEST);
    }
};


SCRY_END_NAMESPACE


#endif
