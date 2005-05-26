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
#ifndef SCRY_PUMP_H
#define SCRY_PUMP_H


#include "OpenGL.h"


namespace scry {

    typedef const void* (*Pump)(const void* data);
    typedef Pump (*PumpFactoryFunction)(GLenum type, int size);

    Pump getIndexPump(GLenum type, int size);
    Pump getVertexPump(GLenum type, int size);
    Pump getColorPump(GLenum type, int size);
    Pump getNormalPump(GLenum type, int size);
    Pump getTexCoordPump(GLenum unit, GLenum type, int size);



    // Multitexturing makes things complicated...

    struct PumpFactory {
    protected:
        /// No polymorphic destruction.
        ~PumpFactory() { }

    public:
        virtual Pump getPump(GLenum type, int size) const = 0;
    };

    struct FunctionPumpFactory : public PumpFactory {
        FunctionPumpFactory(PumpFactoryFunction pff)
        : _pff(pff) {
        }

        Pump getPump(GLenum type, int size) const {
            return _pff(type, size);
        }

    private:
        PumpFactoryFunction _pff;
    };

    struct TexCoordPumpFactory : public PumpFactory {
        TexCoordPumpFactory(GLenum unit)
        : _unit(unit) {
        }

        Pump getPump(GLenum type, int size) const {
            return getTexCoordPump(_unit, type, size);
        }
        
    private:
        GLenum _unit;
    };

}

#endif
