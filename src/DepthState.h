#ifndef SCRY_DEPTH_STATE_H
#define SCRY_DEPTH_STATE_H


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
        }

        static void bind();

        DepthState* clone() const;
        const DepthState& getDefault() const;
        void switchTo(const State& to) const;

        bool getDepthTest() const {
            return _enableDepthTest;
        }

        void setDepthTest(bool depthTest) {
            _enableDepthTest = depthTest;
        }

    private:
        Inited<bool, false> _enableDepthTest;
    };
    SCRY_REF_PTR(DepthState);

}


#endif
