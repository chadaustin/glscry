#ifndef SCRY_MATERIAL_STATE_H
#define SCRY_MATERIAL_STATE_H


#include "OpenGL.h"
#include "State.h"
#include "Types.h"


namespace scry {

    class MaterialState : public State {
    protected:
        ~MaterialState() { }
    
    public:
        static void bind();
        
        void apply();
        void reset();
        
        struct Material {
            Material()
            : ambient(0.2f, 0.2f, 0.2f, 1.0f)
            , diffuse(0.8f, 0.8f, 0.8f, 1.0f)
            , specular(0, 0, 0, 1)
            , emission(0, 0, 0, 1)
            , shininess(0) {
            }
            
            void apply(GLenum to);
            
            Vec4f ambient;
            Vec4f diffuse;
            Vec4f specular;
            Vec4f emission;
            float shininess;
        };
        
        Material front;
        Material back;
    };
    SCRY_REF_PTR(MaterialState);

}


#endif
