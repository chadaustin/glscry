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
#ifndef SCRY_ACTION_H
#define SCRY_ACTION_H


#include "OpenGL.h"
#include "RefCounted.h"


namespace scry {

    class Action : public RefCounted {
    protected:
        ~Action() { }

    public:
        static void bind();

        virtual void execute() = 0;
    };
    SCRY_REF_PTR(Action);


    class ClearAction : public Action {
    protected:
        ~ClearAction() { }

    public:
        static void bind();

        ClearAction(GLbitfield buffers) {
            _buffers = buffers;
        }

        void execute() {
            glClear(_buffers);
        }

    private:
        GLbitfield _buffers;
    };
    SCRY_REF_PTR(ClearAction);


    class FlushAction : public Action {
    protected:
        ~FlushAction() { }

    public:
        static void bind();

        void execute() {
            glFlush();
        }
    };
    SCRY_REF_PTR(FlushAction);


    class FinishAction : public Action {
    protected:
        ~FinishAction() { }

    public:
        static void bind();

        void execute() {
            glFinish();
        }
    };
    SCRY_REF_PTR(FinishAction);

}


#endif
