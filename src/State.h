#ifndef TRIAGARA_STATE_H
#define TRIAGARA_STATE_H


#include "Base.h"


TRIAGARA_BEGIN_NAMESPACE


class State {
public:
    virtual ~State() { }

    virtual void apply() = 0;
    virtual void reset() = 0;
};


TRIAGARA_END_NAMESPACE


#endif
