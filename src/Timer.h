#ifndef SCRY_TIMER_H
#define SCRY_TIMER_H


#include <SDL.h>
#include "Base.h"


SCRY_BEGIN_NAMESPACE

class Timer {
public:
    Timer();

    /// Returns time since creation.
    float elapsed() const;

private:
    Uint32 _last;
};

SCRY_END_NAMESPACE


#endif
