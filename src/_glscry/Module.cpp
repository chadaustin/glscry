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
#include <boost/python/detail/api_placeholder.hpp> // for len()
#include "Context.h"
#include "Platform.h"

#include "BlendState.h"
#include "ColorBufferState.h"
#include "DepthState.h"
#include "LightState.h"
#include "LineState.h"
#include "MaterialState.h"
#include "ShaderState.h"
#include "TextureState.h"

#include "Geometry.h"

#include "ImmediateTest.h"
#include "VertexArrayTest.h"
#include "VertexBufferObjectTest.h"

#include "CopyPixelTest.h"
#include "DrawPixelTest.h"
#include "ReadPixelTest.h"

#include "TextureUploadTest.h"
#include "TextureMemoryTest.h"
#include "Version.h"

using namespace boost::python;
using namespace scry;


void exportGMTL();


BOOST_PYTHON_MODULE(_glscry) {
    // Disable any warnings about converters being registered multiple times.
    object warnings(( handle<>( PyImport_ImportModule("warnings") ) ));
    warnings.attr("filterwarnings")("ignore");

    initContext();

    exportGMTL();
    bindOpenGL();
    bindContext();
    bindPlatform();

    def("getVersion", getVersion);
    def("getBuildID", getBuildID);

    // States.
    StateSet::bind();
    State::bind();
    BlendState::bind();
    ColorBufferState::bind();
    DepthState::bind();
    LightState::bind();
    LineState::bind();
    MaterialState::bind();
    ShaderState::bind();
    TextureState::bind();

    // Actions.
    Action::bind();
    ClearAction::bind();
    FlushAction::bind();
    FinishAction::bind();

    // Geometry generators.

    bindArrayTypes();
    Geometry::bind();

    // Tests.

    Test::bind();

    TextureUploadTest::bind();
    TextureMemoryTest::bind();

    PixelTransferTest::bind();
    CopyPixelTest::bind();
    DrawPixelTest::bind();
    ReadPixelTest::bind();

    GeometryTest::bind();
    ImmediateTest::bind();
    VertexArrayTest::bind();
    VertexBufferObjectTest::bind();

    warnings.attr("resetwarnings")();
}
