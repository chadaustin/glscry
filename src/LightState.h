#ifndef SCRY_LIGHT_STATE_H
#define SCRY_LIGHT_STATE_H


#include <vector>
#include "OpenGL.h"
#include "State.h"
#include "Types.h"


namespace scry {

    class LightState : public State {
    protected:
        ~LightState() { }

    public:
        static void bind();

        LightState();

        void apply();
        void reset();

        struct Light {
            // Defaults for lights 1..n.  light0 is initialized separately.
            Light()
            : enable(false)
            , ambient(0, 0, 0, 1)
            , diffuse(0, 0, 0, 0)
            , specular(0, 0, 0, 0)
            , position(0, 0, 1, 0)
            , spotDirection(0, 0, -1)
            , spotExponent(0)
            , spotCutoff(180)
            , constantAttenuation(1)
            , linearAttenuation(0)
            , quadraticAttenuation(0) {
            }
            
            void apply(GLenum light);
            
            bool operator==(const Light& rhs) const {
                return enable == rhs.enable &&
                       ambient == rhs.ambient &&
                       diffuse == rhs.diffuse &&
                       specular == rhs.specular &&
                       position == rhs.position &&
                       spotDirection == rhs.spotDirection &&
                       spotExponent == rhs.spotExponent &&
                       spotCutoff == rhs.spotCutoff &&
                       constantAttenuation == rhs.constantAttenuation &&
                       linearAttenuation == rhs.linearAttenuation &&
                       quadraticAttenuation == rhs.quadraticAttenuation;
            }
        
            bool enable;
            Vec4f ambient;
            Vec4f diffuse;
            Vec4f specular;
            Vec4f position;
            Vec3f spotDirection;
            float spotExponent;
            float spotCutoff;
            float constantAttenuation;
            float linearAttenuation;
            float quadraticAttenuation;
        };

        std::vector<Light> lights;
    };
    SCRY_REF_PTR(LightState);

}


#endif
