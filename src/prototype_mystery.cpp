// /software/thirdparty/gcc/4.7.2-0.el6_64/bin/g++ -std=c++11 prototype.cpp && ./a.out
#include <iostream>
#include <utility> // std::declval
#include <cstring>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

struct base {
   using prototype_t = int(char const*);
   //SAME AS: typedef int prototype_t(char const*);

   void mf();
   virtual prototype_t mf2 = 0;
   //SAME AS: virtual int mf2(char const*) = 0;
};
struct override: base {
   prototype_t mf2;
   //SAME AS: int mf2(char const*);
   // sadly we cannot use override like:
   //     prototype_t mf2 override;
   //but we can of course
   //     int mf2(char const*) override;
};

int
override::mf2(char const* s) { return strlen(s); }

int process(base& a) {
   std::cout << a.mf2("prototype") << "\n";
   return a.mf2("prototype");
}

base::prototype_t fun;
//SAME AS: int fun(char const*);

BOOST_AUTO_TEST_CASE(test_owner) {
   override b;
   BOOST_CHECK_EQUAL(process(b), 9);
   std::cout << fun("function") << "\n";
   BOOST_CHECK_EQUAL(fun("function"), 24); 

   //std::cout << sizeof(base::prototype_t) << "\n";
   //invalid application ^^^ of ‘sizeof’ to a function type

   //std::cout << sizeof(fun) << "\n";
   //ISO C++ forbids applying ‘sizeof’ to an expression of function type
}

int fun(char const*s) {
   return 3*strlen(s);
}
