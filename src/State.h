#ifndef SCRY_STATE_H
#define SCRY_STATE_H


#include "Base.h"
#include "RefCounted.h"


SCRY_BEGIN_NAMESPACE


class State : public RefCounted {
protected:
    virtual ~State() { }

public:
    virtual void apply() = 0;
    virtual void reset() = 0;
};
typedef boost::intrusive_ptr<State> StatePtr;


SCRY_END_NAMESPACE


#endif
