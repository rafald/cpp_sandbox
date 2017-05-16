#include <functional>
#include <iostream>
#include <type_traits>

///////////////////////////////////////////////////////////////////////////////
// the purpose it to have human readable name for argument
// sometimes we may like to have more specific name then _1 _2

// Hot

// we can provide surplus arguments (how to utilize this?),
// this applies to result of std::bind, it does NOT apply to std::function

// _1 can be ommited in bind and only _2 provide, then first arg of eval call is
// ignored
// When we bind we have to specify ALL arguments, some can be values and some
// placeholders
///////////////////////////////////////////////////////////////////////////////

struct My_2 {
} my_2;

namespace std {
// My_2 is the same as std::placeholders::_2
template <>
struct is_placeholder<My_2> : public integral_constant<int, 2> {};
}  // namespace std

struct My_1 {
} my_1;

namespace std {
template <>
struct is_placeholder<My_1> : public integral_constant<int, 1> {};
}  // namespace std

int
f(int n1, int n2) {
   std::cout << "|calculating " << n1 << "+" << n2 << "|";
   return n1 + n2;
}
int
f3(int n1, int n2, int n3) {
   std::cout << "|calculating " << n1 << "+" << n2 << "+" << n3 << "|";
   return n1 + n2 + n3;
}

int
main() {
   int const ignored_int = 98765;
   {
      using namespace std::placeholders;
      std::function<int(int, int)> sf = f;
      sf(1, 2);
      //    sf(1,2,3,4,5,6); // surplus args are not ignored
      // unless we pass it through bind
      //    std::bind(f,_1,_2, 23423)(1,2,3,4,5,6); // bind itself can NOT receive
      //    surplus args
      std::bind(f, _1, _2)(1, 2, 3, 4, 5, 6);   // but surplus args are accepted in eval call on result of bind!
      std::bind(sf, _1, _2)(1, 2, 3, 4, 5, 6);  // but surplus args are accepted in eval call on result of bind!
                                                //    std::bind(sf,_1,_2, 33)(1,2); // but surplus args are NOT accepted if
                                                //    result of bind is used inside another bind
   }

   std::cout << "Standard placeholder _5 is for the argument number "
             << std::is_placeholder<decltype(std::placeholders::_5)>::value << '\n';

   auto b = std::bind(f, my_2, 2);  // _1 not present so it is ignored in functor b
   // (2 is binded to 2nd arg of f and my_2 becomes new 2nd arg of result of
   // bind)
   std::cout << "Adding 2 to 11 selected with a custom placeholder gives "
             // the first argument, namely 10, is ignored, but can not be skipped
             // in final eval call
             << b(10, 11) << '\n'
             << b(10, 11, 1242342) << '\n';

   std::cout << '\n';

   auto const b_my_2     = std::bind(f, my_1, 2);
   auto const b_my_1     = std::bind(f, 2, my_1);
   auto const b_1        = std::bind(f, 3, std::placeholders::_1);
   auto const b_2        = std::bind(f, 3, std::placeholders::_2);
   auto const b_f3_x_1_2 = std::bind(f3, 3, std::placeholders::_1, std::placeholders::_2);
   std::cout << "Adding 2 to 10 selected with a custom placeholder gives "
             << b_my_2(10, 11)  // the 2nd argument, namely 11, is ignored/redundant
             << '\n'
             << b_my_2(10)  // can skip , 11
             << '\n'
             << b_my_1(10)  // inverses order of args in final call
             << '\n'
             //       << std::bind(f, 2, std::bind(f, 2, std::placeholders::_1), 2 )
             << std::bind(f,
                          2,
                          b_1)(4)  // bind expression can substitute _1 placeholder
             << '\n'
             << std::bind(f, 2, b_2)(ignored_int, 4)  // bind expression can substitute _2 placeholder
             << '\n'
             << std::bind(f, 2, b_f3_x_1_2)(4, 5)  // bind expression can substitute _1 placeholder
             << '\n'
             << std::is_placeholder<typename std::decay<decltype(b_f3_x_1_2)>::type>::value << '\n'
             << std::bind(f, 2, b_f3_x_1_2)(4, 5)  // bind expression can substitute _1 placeholder
             << '\n';
}
