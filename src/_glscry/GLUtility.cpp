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
#include <map>
#include "GLUtility.h"


namespace scry {

    const char* getErrorString(GLenum error) {
        switch (error) {
            case GL_INVALID_ENUM:      return "GL_INVALID_ENUM";
            case GL_INVALID_VALUE:     return "GL_INVALID_VALUE";
            case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
            case GL_STACK_OVERFLOW:    return "GL_STACK_OVERFLOW";
            case GL_STACK_UNDERFLOW:   return "GL_STACK_UNDERFLOW";
            case GL_OUT_OF_MEMORY:     return "GL_OUT_OF_MEMORY";
            case GL_TABLE_TOO_LARGE:   return "GL_TABLE_TOO_LARGE";
            default:                   return "Unknown error";
        }
    }

    void checkOpenGLErrors() {
        GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {
            throw std::runtime_error(getErrorString(error));
        }
    }

}


namespace {

    using namespace scry;

    /// Generic index pump template.
    template<int size, typename T>
    const void* glIndex(const void* data);

    /// Generic vertex pump template.
    template<int size, typename T>
    const void* glVertex(const void* data);

    /// Generic color pump template.
    template<int size, typename T>
    const void* glColor(const void* data);

    /// Generic normal pump template.
    template<int size, typename T>
    const void* glNormal(const void* data);
    
    /// Generic texture coordinate pump template.
    template<GLenum unit, int size, typename T>
    struct glTexCoord;


#define SCRY_DEFINE_PUMP(name, size, wart, type)                        \
    template<>                                                          \
    const void* name<size, type>(const void* data) {                    \
        const type* v = static_cast<const type*>(data);                 \
        name ## size ## wart ## v(v);                                   \
        return v + size;                                                \
    }
    

// Index pumping has a different syntax.  The glIndex OpenGL call
// actually has to do with indexed color.
#define SCRY_DEFINE_INDEX_PUMP(type)                    \
    template<>                                          \
    const void* glIndex<1, type>(const void* data) {    \
        const type* v = static_cast<const type*>(data); \
        glArrayElement(*v);                             \
        return v + 1;                                   \
    }

#define SCRY_DEFINE_VERTEX_PUMP(size, wart, type)       \
    SCRY_DEFINE_PUMP(glVertex, size, wart, type)

#define SCRY_DEFINE_COLOR_PUMP(size, wart, type)        \
    SCRY_DEFINE_PUMP(glColor, size, wart, type)

#define SCRY_DEFINE_NORMAL_PUMP(wart, type)     \
    SCRY_DEFINE_PUMP(glNormal, 3, wart, type)
    
#define SCRY_DEFINE_TEXCOORD_PUMP(size, wart, type)                      \
    template<>                                                           \
    struct glTexCoord<0, size, type> {                                   \
        static const void* pump(const void* data) {                      \
            const type* v = static_cast<const type*>(data);              \
            glTexCoord ## size ## wart ## v(v);                          \
            return v + size;                                             \
        }                                                                \
    };                                                                   \
                                                                         \
    template<GLenum unit>                                                \
    struct glTexCoord<unit, size, type> {                                \
        static const void* pump(const void* data) {                      \
            const type* v = static_cast<const type*>(data);              \
            glMultiTexCoord ## size ## wart ## v(GL_TEXTURE0 + unit, v); \
            return v + size;                                             \
        }                                                                \
    };


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
    
#define SCRY_DEFINE_TEXCOORD_PUMPS(size)            \
    SCRY_DEFINE_TEXCOORD_PUMP(size, s, GLshort);    \
    SCRY_DEFINE_TEXCOORD_PUMP(size, i, GLint);      \
    SCRY_DEFINE_TEXCOORD_PUMP(size, f, GLfloat);    \
    SCRY_DEFINE_TEXCOORD_PUMP(size, d, GLdouble);


    SCRY_DEFINE_INDEX_PUMP(GLubyte);
    SCRY_DEFINE_INDEX_PUMP(GLushort);
    SCRY_DEFINE_INDEX_PUMP(GLuint);

    SCRY_DEFINE_VERTEX_PUMPS(2);
    SCRY_DEFINE_VERTEX_PUMPS(3);
    SCRY_DEFINE_VERTEX_PUMPS(4);

    SCRY_DEFINE_COLOR_PUMPS(3);
    SCRY_DEFINE_COLOR_PUMPS(4);

    SCRY_DEFINE_NORMAL_PUMP(b, GLbyte);
    SCRY_DEFINE_NORMAL_PUMP(s, GLshort);
    SCRY_DEFINE_NORMAL_PUMP(i, GLint);
    SCRY_DEFINE_NORMAL_PUMP(f, GLfloat);
    SCRY_DEFINE_NORMAL_PUMP(d, GLdouble);
    
    SCRY_DEFINE_TEXCOORD_PUMPS(1);
    SCRY_DEFINE_TEXCOORD_PUMPS(2);
    SCRY_DEFINE_TEXCOORD_PUMPS(3);
    SCRY_DEFINE_TEXCOORD_PUMPS(4);


    typedef std::pair<GLenum, int> VectorType;
    typedef std::map<VectorType, Pump> PumpMap;

    typedef std::pair<GLenum, VectorType> TexCoordType;
    typedef std::map<TexCoordType, Pump> TexCoordPumpMap;

    bool g_initialized = false;
    PumpMap         g_indexPumps;
    PumpMap         g_vertexPumps;
    PumpMap         g_colorPumps;
    PumpMap         g_normalPumps;
    TexCoordPumpMap g_texCoordPumps;


    template<int size, typename Type>
    void registerPump(PumpMap& pm, Pump p) {
        pm[VectorType(GLTypeConstant<Type>::Result, size)] = p;
    }

    template<GLenum unit, int size, typename Type>
    void registerTexCoordPump() {
        VectorType vt(GLTypeConstant<Type>::Result, size);
        TexCoordType tct(GL_TEXTURE0 + unit, vt);
        g_texCoordPumps[tct] = glTexCoord<unit, size, Type>::pump;
    }

#define SCRY_REGISTER_PUMP(pm, name, size, type)        \
    registerPump<size, type>(pm, name<size, type>)

#define SCRY_REGISTER_INDEX_PUMP(type)                  \
    SCRY_REGISTER_PUMP(g_indexPumps, glIndex, 1, type)

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

#define SCRY_REGISTER_NORMAL_PUMP(type)                         \
    SCRY_REGISTER_PUMP(g_normalPumps, glNormal, 3, type)

#define SCRY_REGISTER_TEXCOORD_PUMP(unit, size, type)   \
    registerTexCoordPump<unit, size, type>()

#define SCRY_REGISTER_TEXCOORD_PUMP_TYPES(unit, size)      \
    SCRY_REGISTER_TEXCOORD_PUMP(unit, size, GLshort);      \
    SCRY_REGISTER_TEXCOORD_PUMP(unit, size, GLint);        \
    SCRY_REGISTER_TEXCOORD_PUMP(unit, size, GLfloat);      \
    SCRY_REGISTER_TEXCOORD_PUMP(unit, size, GLdouble);

#define SCRY_REGISTER_TEXCOORD_PUMPS(size)          \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(0, size);     \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(1, size);     \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(2, size);     \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(3, size);     \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(4, size);     \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(5, size);     \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(6, size);     \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(7, size);     \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(8, size);     \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(9, size);     \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(10, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(11, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(12, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(13, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(14, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(15, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(16, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(17, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(18, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(19, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(20, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(21, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(22, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(23, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(24, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(25, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(26, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(27, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(28, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(29, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(30, size);    \
    SCRY_REGISTER_TEXCOORD_PUMP_TYPES(31, size);

    void initialize() {
        if (!g_initialized) {
            SCRY_REGISTER_INDEX_PUMP(GLubyte);
            SCRY_REGISTER_INDEX_PUMP(GLushort);
            SCRY_REGISTER_INDEX_PUMP(GLuint);

            SCRY_REGISTER_VERTEX_PUMPS(2);
            SCRY_REGISTER_VERTEX_PUMPS(3);
            SCRY_REGISTER_VERTEX_PUMPS(4);

            SCRY_REGISTER_COLOR_PUMPS(3);
            SCRY_REGISTER_COLOR_PUMPS(4);
            
            SCRY_REGISTER_NORMAL_PUMP(GLbyte);
            SCRY_REGISTER_NORMAL_PUMP(GLshort);
            SCRY_REGISTER_NORMAL_PUMP(GLint);
            SCRY_REGISTER_NORMAL_PUMP(GLfloat);
            SCRY_REGISTER_NORMAL_PUMP(GLdouble);
            
            SCRY_REGISTER_TEXCOORD_PUMPS(1);
            SCRY_REGISTER_TEXCOORD_PUMPS(2);
            SCRY_REGISTER_TEXCOORD_PUMPS(3);
            SCRY_REGISTER_TEXCOORD_PUMPS(4);

            g_initialized = true;
        }
    }

}


namespace scry {

    Pump getIndexPump(GLenum type, int size) {
        initialize();
        return g_indexPumps[VectorType(type, size)];
    }

    Pump getVertexPump(GLenum type, int size) {
        initialize();
        return g_vertexPumps[VectorType(type, size)];
    }

    Pump getColorPump(GLenum type, int size) {
        initialize();
        return g_colorPumps[VectorType(type, size)];
    }

    Pump getNormalPump(GLenum type, int size) {
        initialize();
        return g_normalPumps[VectorType(type, size)];
    }

    Pump getTexCoordPump(GLenum unit, GLenum type, int size) {
        initialize();
        TexCoordType tct(unit, VectorType(type, size));
        return g_texCoordPumps[tct];
    }

}
