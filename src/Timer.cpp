#include "Timer.h"


namespace scry {

    Timer::Timer() {
        _last = SDL_GetTicks();
    }


    float Timer::elapsed() const {
        Uint32 now = SDL_GetTicks();
        return (now - _last) / 1000.0f;
    }

}
