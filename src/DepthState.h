#ifndef SCRY_DEPTH_STATE_H
#define SCRY_DEPTH_STATE_H


#include "OpenGL.h"
#include "State.h"


namespace scry {

    class DepthState : public State {
    protected:
        ~DepthState() { }

    public:
        DepthState() {
        }

        DepthState(const DepthState& rhs) {
            _enableDepthTest = rhs._enableDepthTest;
            _depthFunc       = rhs._depthFunc;
            _depthMask       = rhs._depthMask;
        }

        static void bind();

        DepthState* clone() const;
        const DepthState& getDefault() const;
        void switchTo(const State& to, bool fullStateSwitch) const;

        bool getEnableDepthTest() const      { return _enableDepthTest;   }
        void setEnableDepthTest(bool enable) { _enableDepthTest = enable; }

        GLenum getDepthFunc() const      { return _depthFunc; }
        void   setDepthFunc(GLenum func) { _depthFunc = func; }

        GLboolean getDepthMask() const         { return _depthMask; }
        void      setDepthMask(GLboolean mask) { _depthMask = mask; }

    private:
        Inited<bool, false>        _enableDepthTest;
        Inited<GLenum, GL_LESS>    _depthFunc;
        Inited<GLboolean, GL_TRUE> _depthMask;
    };
    SCRY_REF_PTR(DepthState);

}


#endif
