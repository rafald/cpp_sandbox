// No main here! #define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// https://www.youtube.com/watch?v=qHgM5UdzPQU
// https://www.youtube.com/watch?v=_Ny6Qbm_uMI

namespace constexpr_tests {

// good for handling void return type in generic functions /but not always/
BOOST_AUTO_TEST_SUITE(constexpr_tests)

BOOST_AUTO_TEST_CASE(simple_test) {}

BOOST_AUTO_TEST_SUITE_END()
}  // namespace constexpr_tests
