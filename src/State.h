#ifndef SCRY_STATE_H
#define SCRY_STATE_H


#include "Base.h"


SCRY_BEGIN_NAMESPACE


class State {
public:
    virtual ~State() { }

    virtual void apply() = 0;
    virtual void reset() = 0;
};


SCRY_END_NAMESPACE


#endif
