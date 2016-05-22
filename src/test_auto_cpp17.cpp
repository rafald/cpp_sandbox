#include <stack>
#include <vector>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

int f(auto const &c1, auto const &c2) { return sizeof(c1) + c2.size(); }

BOOST_AUTO_TEST_CASE(test) {
  //  auto gl = [](Assignable& a, auto* b) { a = *b; };

  std::vector<int> a;
  std::stack<int> b;
  BOOST_CHECK_EQUAL(f(a, b), 24);
}
