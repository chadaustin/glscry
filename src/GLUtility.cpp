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
    template<int size, typename T>
    const void* glTexCoord(const void* data);

    /// Generic indexe pump template.
    template<int size, typename T>
    const void* glIndex(const void* data);


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

#define SCRY_DEFINE_NORMAL_PUMP(wart, type)     \
    SCRY_DEFINE_PUMP(glNormal, 3, wart, type)
    
#define SCRY_DEFINE_TEXCOORD_PUMP(size, wart, type) \
    SCRY_DEFINE_PUMP(glTexCoord, size, wart, type)

// Index pumping has a different syntax.  The glIndex OpenGL call
// actually has to do with indexed color.
#define SCRY_DEFINE_INDEX_PUMP(type)                    \
    template<>                                          \
    const void* glIndex<1, type>(const void* data) {    \
        const type* v = static_cast<const type*>(data); \
        glArrayElement(*v);                             \
        return v + 1;                                   \
    }


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

    SCRY_DEFINE_INDEX_PUMP(GLubyte);
    SCRY_DEFINE_INDEX_PUMP(GLushort);
    SCRY_DEFINE_INDEX_PUMP(GLuint);


    typedef std::pair<GLenum, int> VectorType;
    typedef std::map<VectorType, Pump> PumpMap;

    bool g_initialized = false;
    PumpMap g_vertexPumps;
    PumpMap g_colorPumps;
    PumpMap g_normalPumps;
    PumpMap g_texCoordPumps;
    PumpMap g_indexPumps;


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

#define SCRY_REGISTER_NORMAL_PUMP(type)                         \
    SCRY_REGISTER_PUMP(g_normalPumps, glNormal, 3, type)

#define SCRY_REGISTER_TEXCOORD_PUMPS(size)                              \
    SCRY_REGISTER_PUMP(g_texCoordPumps, glTexCoord, size, GLshort);     \
    SCRY_REGISTER_PUMP(g_texCoordPumps, glTexCoord, size, GLint);       \
    SCRY_REGISTER_PUMP(g_texCoordPumps, glTexCoord, size, GLfloat);     \
    SCRY_REGISTER_PUMP(g_texCoordPumps, glTexCoord, size, GLdouble);

#define SCRY_REGISTER_INDEX_PUMP(type)                  \
    SCRY_REGISTER_PUMP(g_indexPumps, glIndex, 1, type)

    void initialize() {
        if (!g_initialized) {
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

            SCRY_REGISTER_INDEX_PUMP(GLubyte);
            SCRY_REGISTER_INDEX_PUMP(GLushort);
            SCRY_REGISTER_INDEX_PUMP(GLuint);

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

    Pump getNormalPump(GLenum type, int size) {
        initialize();
        return g_normalPumps[VectorType(type, size)];
    }
    
    Pump getTexCoordPump(GLenum type, int size) {
        initialize();
        return g_texCoordPumps[VectorType(type, size)];
    }

    Pump getIndexPump(GLenum type, int size) {
        initialize();
        return g_indexPumps[VectorType(type, size)];
    }

}
