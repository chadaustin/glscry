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
#ifndef SCRY_BLEND_STATE_H
#define SCRY_BLEND_STATE_H


#include "OpenGL.h"
#include "State.h"


namespace scry {

    class BlendState : public State {
    protected:
        ~BlendState() { }

    public:
        BlendState() {
        }

        BlendState(const BlendState& rhs) {
            _enableBlend = rhs._enableBlend;
            _srcFactor   = rhs._srcFactor;
            _dstFactor   = rhs._dstFactor;
        }

        static void bind();

        BlendState* clone() const;
        const BlendState& getDefault() const;
        void switchTo(const State& to, bool fullStateSwitch) const;

        bool getEnableBlend() const      { return _enableBlend;   }
        void setEnableBlend(bool enable) { _enableBlend = enable; }

        GLenum getSrcFactor() const        { return _srcFactor; }
        void   setSrcFactor(GLenum factor) { _srcFactor = factor; }

        GLenum getDstFactor() const        { return _dstFactor; }
        void   setDstFactor(GLenum factor) { _dstFactor = factor; }

    private:
        Inited<bool, false>     _enableBlend;
        Inited<GLenum, GL_ONE>  _srcFactor;
        Inited<GLenum, GL_ZERO> _dstFactor;
    };
    SCRY_REF_PTR(BlendState);

}


#endif
