#ifndef TRIAGARA_DEPTH_STATE_H
#define TRIAGARA_DEPTH_STATE_H


#include "State.h"


TRIAGARA_BEGIN_NAMESPACE


class DepthState : public State {
    void apply() {
        glEnable(GL_DEPTH_TEST);
    }

    void reset() {
        glDisable(GL_DEPTH_TEST);
    }
};


TRIAGARA_END_NAMESPACE


#endif
