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
        MaterialState() {
        }

        MaterialState(const MaterialState& rhs) {
            front = rhs.front;
            back  = rhs.back;
        }

        static void bind();

        MaterialState* clone() const;
        const MaterialState& getDefault() const;
        void switchTo(const State& to, bool fullStateSwitch) const;

        struct Material {
            Material()
            : ambient(0.2f, 0.2f, 0.2f, 1.0f)
            , diffuse(0.8f, 0.8f, 0.8f, 1.0f)
            , specular(0, 0, 0, 1)
            , emission(0, 0, 0, 1)
            , shininess(0) {
            }

            void switchTo(const Material& m, GLenum face,
                          bool fullStateSwitch) const;
            
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
