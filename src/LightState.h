#ifndef SCRY_LIGHT_STATE_H
#define SCRY_LIGHT_STATE_H


#include <vector>
#include "glew.h"
#include "State.h"


SCRY_BEGIN_NAMESPACE


class LightState : public State {
protected:
    ~LightState() { }

public:
    static void bind();

    LightState() {
        GLint max_lights;
        glGetIntegerv(GL_MAX_LIGHTS, &max_lights);
        _lights.resize(max_lights);
    }

    void useLight(size_t index, bool use) {
        SCRY_ASSERT(index < _lights.size());
        _lights[index].use = use;
    }

    void setAmbient(size_t index, const Vec4f& ambient) {
        SCRY_ASSERT(index < _lights.size());
        _lights[index].ambient = ambient;
    }

    void apply() {
        glEnable(GL_LIGHTING);
        for (size_t i = 0; i < _lights.size(); ++i) {
            Light& l = _lights[i];
            if (l.use) {
                glEnable(GL_LIGHT0 + i);
                glLightfv(GL_LIGHT0 + i, GL_AMBIENT, l.ambient.getData());
            }
        }
    }

    void reset() {
        for (size_t i = 0; i < _lights.size(); ++i) {
            glDisable(GL_LIGHT0 + i);
        }
        glDisable(GL_LIGHTING);
    }

private:
    struct Light {
        Light() {
            use = false;
            ambient = Vec4f(0, 0, 0, 1);
        }

        bool use;
        Vec4f ambient;
    };

    std::vector<Light> _lights;
};
SCRY_REF_PTR(LightState);


SCRY_END_NAMESPACE


#endif
