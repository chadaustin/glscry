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
#include <boost/python.hpp>
#include "OpenGL.h"
using namespace boost::python;

namespace scry {

    std::string glGetString(GLenum name) {
        const GLubyte* str = ::glGetString(name);
        return str ? reinterpret_cast<const char*>(str) : "";
    }

    void bindOpenGL() {
#define DEF(name) scope().attr((#name)) = (name)

        // Boolean.
        DEF(GL_TRUE);
        DEF(GL_FALSE);

        // Data types.
        DEF(GL_BYTE);
        DEF(GL_UNSIGNED_BYTE);
        DEF(GL_SHORT);
        DEF(GL_UNSIGNED_SHORT);
        DEF(GL_INT);
        DEF(GL_UNSIGNED_INT);
        DEF(GL_FLOAT);

        // Primitive types.
        DEF(GL_POINTS);
        DEF(GL_LINES);
        DEF(GL_LINE_STRIP);
        DEF(GL_LINE_LOOP);
        DEF(GL_TRIANGLES);
        DEF(GL_TRIANGLE_STRIP);
        DEF(GL_TRIANGLE_FAN);
        DEF(GL_QUADS);
        DEF(GL_QUAD_STRIP);
        DEF(GL_POLYGON);

        // VBO types.
        DEF(GL_STREAM_DRAW_ARB);
        DEF(GL_STREAM_READ_ARB);
        DEF(GL_STREAM_COPY_ARB);
        DEF(GL_STATIC_DRAW_ARB);
        DEF(GL_STATIC_READ_ARB);
        DEF(GL_STATIC_COPY_ARB);
        DEF(GL_DYNAMIC_DRAW_ARB);
        DEF(GL_DYNAMIC_READ_ARB);
        DEF(GL_DYNAMIC_COPY_ARB);

        // glCopyPixels types.
        DEF(GL_COLOR);
        DEF(GL_DEPTH);
        DEF(GL_STENCIL);

        // Pixel transfer formats.
        DEF(GL_COLOR_INDEX);
        DEF(GL_STENCIL_INDEX);
        DEF(GL_DEPTH_COMPONENT);
        DEF(GL_RED);
        DEF(GL_GREEN);
        DEF(GL_BLUE);
        DEF(GL_ALPHA);
        DEF(GL_RGB);
        DEF(GL_BGR);
        DEF(GL_RGBA);
        DEF(GL_BGRA);
        DEF(GL_LUMINANCE);
        DEF(GL_LUMINANCE_ALPHA);

        DEF(GL_NEAREST);
        DEF(GL_LINEAR);
        DEF(GL_NEAREST_MIPMAP_NEAREST);
        DEF(GL_LINEAR_MIPMAP_NEAREST);
        DEF(GL_NEAREST_MIPMAP_LINEAR);
        DEF(GL_LINEAR_MIPMAP_LINEAR);

        DEF(GL_CLAMP);
        DEF(GL_CLAMP_TO_EDGE);
        DEF(GL_REPEAT);

        DEF(GL_VENDOR);
        DEF(GL_RENDERER);
        DEF(GL_VERSION);
        DEF(GL_EXTENSIONS);

        DEF(GL_COLOR_BUFFER_BIT);
        DEF(GL_DEPTH_BUFFER_BIT);
        DEF(GL_ACCUM_BUFFER_BIT);
        DEF(GL_STENCIL_BUFFER_BIT);

        DEF(GL_NEVER);
        DEF(GL_LESS);
        DEF(GL_LEQUAL);
        DEF(GL_EQUAL);
        DEF(GL_GREATER);
        DEF(GL_NOTEQUAL);
        DEF(GL_GEQUAL);
        DEF(GL_ALWAYS);

        DEF(GL_ZERO);
        DEF(GL_ONE);
        DEF(GL_SRC_COLOR);
        DEF(GL_ONE_MINUS_SRC_COLOR);
        DEF(GL_DST_COLOR);
        DEF(GL_ONE_MINUS_DST_COLOR);
        DEF(GL_SRC_ALPHA);
        DEF(GL_ONE_MINUS_SRC_ALPHA);
        DEF(GL_DST_ALPHA);
        DEF(GL_ONE_MINUS_DST_ALPHA);
        DEF(GL_SRC_ALPHA_SATURATE);

        def("glGetString", glGetString);
    }

}
