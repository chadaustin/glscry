#include <map>
#include "GLUtility.h"


namespace {

    using namespace scry;

    /// Generic vertex pump template.
    template<int size, typename T>
    const void* glVertex(const void* data);

    /// Generic color pump template.
    template<int size, typename T>
    const void* glColor(const void* data);


#define SCRY_DEFINE_PUMP(name, size, wart, type)                        \
    template<>                                                          \
    inline const void* name<size, type>(const void* data) {             \
        const type* v = static_cast<const type*>(data);                 \
        name ## size ## wart ## v(v);                                   \
        return v + size;                                                \
    }
    

#define SCRY_DEFINE_VERTEX_PUMP(size, wart, type)       \
    SCRY_DEFINE_PUMP(glVertex, size, wart, type)

#define SCRY_DEFINE_COLOR_PUMP(size, wart, type)        \
    SCRY_DEFINE_PUMP(glColor, size, wart, type)


#define SCRY_DEFINE_VERTEX_PUMPS(size)                      \
    SCRY_DEFINE_VERTEX_PUMP(size, s, GLshort);              \
    SCRY_DEFINE_VERTEX_PUMP(size, i, GLint);                \
    SCRY_DEFINE_VERTEX_PUMP(size, f, GLfloat);              \
    SCRY_DEFINE_VERTEX_PUMP(size, d, GLdouble);

#define SCRY_DEFINE_COLOR_PUMPS(size)              \
    SCRY_DEFINE_COLOR_PUMP(size, b,  GLbyte);      \
    SCRY_DEFINE_COLOR_PUMP(size, ub, GLubyte);     \
    SCRY_DEFINE_COLOR_PUMP(size, s,  GLshort);     \
    SCRY_DEFINE_COLOR_PUMP(size, us, GLushort);    \
    SCRY_DEFINE_COLOR_PUMP(size, i,  GLint);       \
    SCRY_DEFINE_COLOR_PUMP(size, ui, GLuint);      \
    SCRY_DEFINE_COLOR_PUMP(size, f,  GLfloat);     \
    SCRY_DEFINE_COLOR_PUMP(size, d,  GLdouble);


    SCRY_DEFINE_VERTEX_PUMPS(2);
    SCRY_DEFINE_VERTEX_PUMPS(3);
    SCRY_DEFINE_VERTEX_PUMPS(4);

    SCRY_DEFINE_COLOR_PUMPS(3);
    SCRY_DEFINE_COLOR_PUMPS(4);


    typedef std::pair<GLenum, int> VectorType;
    typedef std::map<VectorType, Pump> PumpMap;

    bool g_initialized = false;
    PumpMap g_vertexPumps;
    PumpMap g_colorPumps;


    template<int size, typename Type>
    void registerPump(PumpMap& pm, Pump p) {
        pm[VectorType(GLTypeConstant<Type>::Result, size)] = p;
    }

#define SCRY_REGISTER_PUMP(pm, name, size, type)        \
    registerPump<size, type>(pm, name<size, type>)

#define SCRY_REGISTER_VERTEX_PUMPS(size)                                \
    SCRY_REGISTER_PUMP(g_vertexPumps, glVertex, size, GLshort);         \
    SCRY_REGISTER_PUMP(g_vertexPumps, glVertex, size, GLint);           \
    SCRY_REGISTER_PUMP(g_vertexPumps, glVertex, size, GLfloat);         \
    SCRY_REGISTER_PUMP(g_vertexPumps, glVertex, size, GLdouble);

#define SCRY_REGISTER_COLOR_PUMPS(size)                           \
    SCRY_REGISTER_PUMP(g_colorPumps, glColor, size, GLbyte);      \
    SCRY_REGISTER_PUMP(g_colorPumps, glColor, size, GLubyte);     \
    SCRY_REGISTER_PUMP(g_colorPumps, glColor, size, GLshort);     \
    SCRY_REGISTER_PUMP(g_colorPumps, glColor, size, GLushort);    \
    SCRY_REGISTER_PUMP(g_colorPumps, glColor, size, GLint);       \
    SCRY_REGISTER_PUMP(g_colorPumps, glColor, size, GLuint);      \
    SCRY_REGISTER_PUMP(g_colorPumps, glColor, size, GLfloat);     \
    SCRY_REGISTER_PUMP(g_colorPumps, glColor, size, GLdouble);

    void initialize() {
        if (!g_initialized) {
            SCRY_REGISTER_VERTEX_PUMPS(2);
            SCRY_REGISTER_VERTEX_PUMPS(3);
            SCRY_REGISTER_VERTEX_PUMPS(4);

            SCRY_REGISTER_COLOR_PUMPS(3);
            SCRY_REGISTER_COLOR_PUMPS(4);
            
            g_initialized = true;
        }
    }

}


namespace scry {

    Pump getVertexPump(GLenum type, int size) {
        initialize();
        return g_vertexPumps[VectorType(type, size)];
    }

    Pump getColorPump(GLenum type, int size) {
        initialize();
        return g_colorPumps[VectorType(type, size)];
    }

//    Pump getNormalPump(GLenum type, int size) {
//        initialize();
//        return g_normalPumps[VectorType(type, size)];
//    }

}
