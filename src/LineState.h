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
#ifndef SCRY_LINE_STATE_H
#define SCRY_LINE_STATE_H


#include "OpenGL.h"
#include "State.h"


namespace scry {

    class LineState : public State {
    protected:
        ~LineState() { }

    public:
        static void bind();

        LineState() {
            _enableSmooth   = false;
            _enableStipple  = false;
            _stippleFactor  = 1;
            _stipplePattern = 0xFFFF;
            _width          = 1.0f;
        }

        LineState(const LineState& rhs) {
            _enableSmooth   = rhs._enableSmooth;
            _enableStipple  = rhs._enableStipple;
            _stippleFactor  = rhs._stippleFactor;
            _stipplePattern = rhs._stipplePattern;
            _width          = rhs._width;
        }

        LineState* clone() const;
        const LineState& getDefault() const;
        void switchTo(const State& to, bool fullStateSwitch) const;

        bool getEnableSmooth() const      { return _enableSmooth;   }
        void setEnableSmooth(bool enable) { _enableSmooth = enable; }

        bool getEnableStipple() const      { return _enableStipple;   }
        void setEnableStipple(bool enable) { _enableStipple = enable; }

        GLint getStippleFactor() const      { return _stippleFactor;   }
        void setStippleFactor(GLint factor) { _stippleFactor = factor; }

        GLushort getStipplePattern() const       { return _stipplePattern;    }
        void setStipplePattern(GLushort pattern) { _stipplePattern = pattern; }

        float getWidth() const     { return _width;  }
        void setWidth(float width) { _width = width; }

    private:
        bool     _enableSmooth;
        bool     _enableStipple;
        GLint    _stippleFactor;
        GLushort _stipplePattern;
        float    _width;
    };
    SCRY_REF_PTR(LineState);

}


#endif
