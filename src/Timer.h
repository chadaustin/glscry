#ifndef SCRY_TIMER_H
#define SCRY_TIMER_H


#include <SDL.h>


namespace scry {

    class Timer {
    public:
        Timer();

        /// Returns time since creation.
        float elapsed() const;

    private:
        Uint32 _last;
    };

}


#endif
