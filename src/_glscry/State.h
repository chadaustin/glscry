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
        virtual void switchTo(const State& to, bool fullStateSwitch) const = 0;
    };
    SCRY_REF_PTR(State);

}


#endif
