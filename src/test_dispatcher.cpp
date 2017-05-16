#include "dispatcher.h"

//#include <algorithm>
#include <iostream>

#if 1

#define BOOST_TEST_MODULE dispatcher
//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#else
#define BOOST_TEST_MAIN ...
#include <boost/test/included/unit_test.hpp>
#endif

using namespace std;

BOOST_AUTO_TEST_CASE(instantiate_dispatcher) {
   OptimisticDispatcher<function<void(uint32_t, string)>> event;

   auto subscriber =
       event.add([](auto number, auto text) { cout << "Number was " << number << " and text was " << text << endl; });

   event.invoke(42, "Hello Universe!");

   // the subscriber is removed from event here automatically
   // BOOST_CHECK( test_object.is_valid() );
}
