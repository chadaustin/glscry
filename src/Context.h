#ifndef TRIAGARA_CONTEXT_H
#define TRIAGARA_CONTEXT_H


#include <SDL.h>
#include "Base.h"


TRIAGARA_BEGIN_NAMESPACE

inline void pumpMessages() {
    SDL_Event event;
    int result = SDL_PollEvent(&event);
    while (result == 1) {
        if (event.type == SDL_QUIT) {
            exit(EXIT_FAILURE);
        }

        result = SDL_PollEvent(&event);
    }
}

TRIAGARA_END_NAMESPACE


#endif
