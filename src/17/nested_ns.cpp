// No main here! #define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

namespace a::b::c::dd {
   struct XY { int i ; };
}

BOOST_AUTO_TEST_CASE(test_nested_ns) {
   a::b::c::dd::XY xy = {};
   BOOST_CHECK_EQUAL(xy.i, 0);
}


