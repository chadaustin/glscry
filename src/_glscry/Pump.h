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
