#include <boost/python.hpp>
#include <boost/python/detail/api_placeholder.hpp> // for len()
#include "Context.h"

#include "BlendState.h"
#include "ColorBufferState.h"
#include "DepthState.h"
#include "LightState.h"
#include "MaterialState.h"
#include "TextureState.h"

#include "Geometry.h"

#include "ImmediateTest.h"
#include "DisplayListTest.h"
#include "VertexArrayTest.h"
#include "CompiledVertexArrayTest.h"
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

    def("getVersion", getVersion);
    def("getBuildID", getBuildID);

    // States.
    StateSet::bind();
    State::bind();
    BlendState::bind();
    ColorBufferState::bind();
    DepthState::bind();
    LightState::bind();
    MaterialState::bind();
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
    DisplayListTest::bind();
    VertexArrayTest::bind();
    CompiledVertexArrayTest::bind();
    VertexBufferObjectTest::bind();

    warnings.attr("resetwarnings")();
}
