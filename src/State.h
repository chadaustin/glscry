#ifndef SCRY_STATE_H
#define SCRY_STATE_H


#include "RefCounted.h"


namespace scry {

    class State : public RefCounted {
    protected:
        virtual ~State() { }

    public:
        static void bind();

        virtual const State& getDefault() const = 0;
        virtual State* clone() const = 0;
        virtual void switchTo(const State& to) const = 0;
    };
    SCRY_REF_PTR(State);

}


#endif
