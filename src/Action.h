#ifndef SCRY_ACTION_H
#define SCRY_ACTION_H


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

        void execute();
    };
    SCRY_REF_PTR(ClearAction);

}


#endif
