#include "Range.h"
using namespace boost::python;


namespace scry {

    void Range::bind() {
        class_<Range, RangePtr, boost::noncopyable>("Range", no_init);
    }

    void LinearRange::bind() {
        class_<LinearRange, LinearRangePtr, boost::noncopyable>
            ("LinearRange", no_init)
            .def(init< float, float, optional<float> >());
        
        implicitly_convertible<LinearRangePtr, RangePtr>();
    }

    void PowerRange::bind() {
        class_<PowerRange, PowerRangePtr, boost::noncopyable>
            ("PowerRange", no_init)
            .def(init< float, float, optional<float> >());

        implicitly_convertible<PowerRangePtr, RangePtr>();
    }

}
