#ifndef TRIAGARA_TIMER_H
#define TRIAGARA_TIMER_H


#include <SDL.h>
#include "Base.h"


TRIAGARA_BEGIN_NAMESPACE

class Timer {
public:
    Timer();

    /// Returns time since creation.
    float elapsed() const;

private:
    Uint32 _last;
};

TRIAGARA_END_NAMESPACE


#endif
