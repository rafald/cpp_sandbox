#define GSL_THROW_ON_CONTRACT_VIOLATION  // GSL_TERMINATE_ON_CONTRACT_VIOLATION
#include "gsl/gsl"

// No main here! #define BOOST_TEST_MAIN
#include "boost/test/unit_test.hpp"

#include <functional>
#include <vector>


using namespace std;
using namespace gsl;

// using int_bounds_t = static_bounds<34>;
// BOOST_TEST_DONT_PRINT_LOG_VALUE(int_bounds_t)
namespace boost {
namespace test_tools {
   namespace tt_detail {
      template <long int... Ranges>
      struct print_log_value<static_bounds<Ranges...>> {
         void
         operator()(std::ostream &, static_bounds<Ranges...> const &) {}
      };
   }  // namespace tt_detail
}  // namespace test_tools
}  // namespace boost

//#define CONFIRM_COMPILATION_ERRORS
namespace n_bounds_test {
void
use(std::ptrdiff_t &) {}

BOOST_AUTO_TEST_SUITE(bounds_test)
BOOST_AUTO_TEST_CASE(basic_bounds) {
   for (auto point : static_bounds<dynamic_range, 3, 4>{2}) {
      for (decltype(point)::size_type j = 0; j < static_cast<decltype(point)::size_type>(decltype(point)::rank); j++) {
         use(j);
         use(point[j]);
      }
   }
}
BOOST_AUTO_TEST_CASE(bounds_basic) {
   static_bounds<3, 4, 5> b;
   auto                   a = b.slice();
   (void)a;
   static_bounds<4, dynamic_range, 2> x{4};
   x.slice().slice();
}

BOOST_AUTO_TEST_CASE(arrayview_iterator) {
   static_bounds<4, dynamic_range, 2> bounds{3};

   auto itr = bounds.begin();
   (void)itr;
#ifdef CONFIRM_COMPILATION_ERRORS
   span<int, 4, dynamic_range, 2> av(nullptr, bounds);

   auto itr2 = av.cbegin();

   for (auto &v : av) { v = 4; }
   fill(av.begin(), av.end(), 0);
#endif
}

BOOST_AUTO_TEST_CASE(bounds_convertible) {
   static_bounds<7, 4, 2>             b1;
   static_bounds<7, dynamic_range, 2> b2 = b1;
   (void)b2;
// TODO b4 should be b4_compile_error
#ifdef CONFIRM_COMPILATION_ERRORS
   static_bounds<7, dynamic_range, 1> b4 = b2;
#endif

   static_bounds<dynamic_range, dynamic_range, dynamic_range> b3 = b1;
   static_bounds<7, 4, 2>                                     b4 = b3;
   (void)b4;

   static_bounds<dynamic_range> b11;

   static_bounds<dynamic_range> b5;
   static_bounds<34>            b6;

   b5 = static_bounds<20>();
   BOOST_CHECK_THROW(b6 = b5, fail_fast);
   b5 = static_bounds<34>();
   b6 = b5;

   BOOST_CHECK_EQUAL(b5, b6);
   BOOST_CHECK_EQUAL(b5.size(), b6.size());
}

BOOST_AUTO_TEST_SUITE_END()
}  // namespace n_bounds_test
