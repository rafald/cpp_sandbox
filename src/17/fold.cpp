// No main here! #define BOOST_TEST_MAIN

// atom editor screws up! #if __has_include(<boost / test / unit_test.hpp>)
// inserts surplus spaces
#if __has_include(<algorithm>)
#include <boost/test/unit_test.hpp>
#endif

namespace fold_tests {

template <class... T> auto sum(T... t) {
  // t + ... ;  // <- this does not work - parentheses required
  (t + ...);
  return (t + ...); // ... are replaced recursively
}

template <class... T> auto div(T... t) { return (... / t); }

template <class... T> auto div2(T... t) { return (t / ...); }

template <class... T> auto f(T... t) {
  return (t / ... / 10.);
} // ??? this 10 is not init or not - repeated s orather not, why?

template <class... T> auto avg(T... t) { return (t + ...) / sizeof...(t); }

template <class... T> auto f_init(T... t) {
  return (t + ... + 1);
} // with r init value
template <class... T> auto f_linit(T... t) {
  return (
      2 * ... *
      t); // * must be the same operator: mismatched operator in fold-expression
} // with l init value

BOOST_AUTO_TEST_SUITE(fold_tests)

BOOST_AUTO_TEST_CASE(sum_test) { BOOST_CHECK_EQUAL(sum(1, 2, 3, 0, 4, 5), 15); }

BOOST_AUTO_TEST_CASE(div_test) {
  BOOST_CHECK_EQUAL(div(1., 2., 3.), (1. / 2.) / 3.);  // 0.16666666666666666
  BOOST_CHECK_EQUAL(div2(1., 2., 3.), 1. / (2. / 3.)); // 1.5
  BOOST_CHECK_EQUAL(f(2.), 2. / 10.);                  // !!!!  /10.
  // BOOST_CHECK_CLOSE(f(1., 2., 4.), 1. / (2. / 4. / 10.) / 10., 0.00001);
  BOOST_CHECK_EQUAL(f(1., 2., 4.), 1. / (2. / (4. / 10.)));
  BOOST_CHECK_EQUAL(avg(1., 2., 3., 4., 5.), 3);

  BOOST_CHECK_EQUAL(f_init(1., 2., 3., 4., 5.),
                    1. + 2. + 3. + 4. + 5. + 1); // 16
  BOOST_CHECK_EQUAL(f_linit(1., 2., 3., 4., 5.),
                    2 * 1. * 2. * 3. * 4. * 5.); // 240
}

BOOST_AUTO_TEST_SUITE_END()
}
