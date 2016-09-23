#include <map>
#include <string>
#include <iostream>

// No main here! #define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

std::pair<int,float>
f() { return {}; }

BOOST_AUTO_TEST_CASE(test_nested_ns) {
   auto [ x, y ] = f();

   std::map<int,std::string> m;
   for( const auto & [k,v] : m) {
      std::cout << "key:" << k << " value: " << v << "\n";
   }
   BOOST_CHECK_EQUAL(m.size(), 0);
}

