// No main here! #define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

namespace fold_tests {

template <class... T> auto sum(T... t) {
  // t + ... ;  // <- this does not work - parentheses required
  (t + ...);
  return (t + ...);
}

template <class... T> auto div(T... t) { return (... / t); }

template <class... T> auto div2(T... t) { return (t / ...); }

BOOST_AUTO_TEST_SUITE(fold_tests)

BOOST_AUTO_TEST_CASE(sum_test) { BOOST_CHECK_EQUAL(sum(1, 2, 3, 0, 4, 5), 15); }

BOOST_AUTO_TEST_CASE(div_test) {
  BOOST_CHECK_EQUAL(div(1., 2., 3.), (1. / 2.) / 3.);  // 0.16666666666666666
  BOOST_CHECK_EQUAL(div2(1., 2., 3.), 1. / (2. / 3.)); // 1.5
}

BOOST_AUTO_TEST_SUITE_END()
}
