/* [Begin Copyright Header]
 *
 * GLScry - OpenGL Performance Analysis Tool
 * Copyright (C) 2004-2005  Iowa State University
 * 
 * This software is licensed under the terms of the GNU Lesser Public
 * License, version 2.1, as published by the Free Software Foundation.
 * See the file COPYRIGHT.txt for details.
 * 
 * Authors:
 *   Chad Austin <aegisk@iastate.edu>
 *   Dirk Reiners <dreiners@iastate.edu>
 *
 * [End Copyright Header] */
#include <stdexcept>
#include <boost/python.hpp>
#include <SDL.h>
#include "Context.h"
using namespace boost::python;


namespace scry {

    void pumpMessages() {
        SDL_Event event;
        int result = SDL_PollEvent(&event);
        while (result == 1) {
            if (event.type == SDL_QUIT) {
                exit(EXIT_FAILURE);
            }

            result = SDL_PollEvent(&event);
        }
    }


    void throwSDLError(const std::string& prefix) {
        throw std::runtime_error(prefix + ": " + SDL_GetError());
    }


    void initializeSDL(int initflags) {
        if (SDL_Init(initflags) < 0) {
            throwSDLError("SDL initialization failed");
        }
    }


    void throwGLEWError(const std::string& prefix, GLenum error) {
        throw std::runtime_error(
            prefix + ": " +
            reinterpret_cast<const char*>(glewGetErrorString(error)));
    }


    // Evil macros.

    #ifdef NEAR
    #undef NEAR
    #endif

    #ifdef FAR
    #undef FAR
    #endif


    const int    WIDTH  = 1024;
    const int    HEIGHT = 768;
    const double NEAR   = -10000.0;
    const double FAR    = 10000.0;


    void setProjection() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Is this right?
        glOrtho(0, WIDTH, HEIGHT, 0, NEAR, FAR);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }


    void initContext() {
        initializeSDL(SDL_INIT_NOPARACHUTE | SDL_INIT_VIDEO | SDL_INIT_TIMER);
    
        // define our minimum requirements for the GL window
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     5);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   5);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    5);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,   16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        int mode = SDL_OPENGL | SDL_ANYFORMAT;
        const bool fullscreen = false;
        if (fullscreen) {
            mode |= SDL_FULLSCREEN;
        }

        // If we set this before opening the window, the window has
        // this caption.
        SDL_WM_SetCaption("GLScry", 0);

        /**
         * @note SDL does silly things when the created window is larger
         * than the desktop.
         */
        if (!SDL_SetVideoMode(WIDTH, HEIGHT, 32, mode)) {
            throwSDLError("Setting video mode failed");
        }

        GLenum glewError = glewInit();
        if (glewError != GLEW_OK) {
            throwGLEWError("Initializing GLEW failed", glewError);
        }

        setProjection();

        SDL_ShowCursor(SDL_DISABLE);
    }


    void flip() {
        SDL_GL_SwapBuffers();
    }

    void betweenTests() {
        glClear(GL_COLOR_BUFFER_BIT);
        pumpMessages();
        flip();
    }

    void bindContext() {
        def("flip", flip);
        def("betweenTests", betweenTests);
    }


}
