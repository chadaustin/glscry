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
