#ifndef SCRY_STATE_H
#define SCRY_STATE_H


#include "Base.h"
#include "RefCounted.h"


SCRY_BEGIN_NAMESPACE


class State : public RefCounted {
protected:
    virtual ~State() { }

public:
    static void bind();

    virtual void apply() = 0;
    virtual void reset() = 0;
};
SCRY_REF_PTR(State);


SCRY_END_NAMESPACE


#endif
