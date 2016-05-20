#include <locale>
#include <string>
#include <iostream>

using namespace std::literals::string_literals;

// Declaration of the concept "EqualityComparable", which is satisfied by
// any type T such that for values a and b of type T,
// the expression a==b compiles and its result is convertible to bool
template<typename T>
concept bool EqualityComparable = requires(T a, T b) {
    { a == b } -> bool;
};
 
void f(EqualityComparable&&); // declaration of a constrained function template
// template<typename T>
// void f(T&&) requires EqualityComparable<T>; // long form of the same

int
main()
{ 
  f("abc"s); // OK, std::string is EqualityComparable
//  f(std::use_facet<std::ctype<char>>(std::locale{})); // Error: not EqualityComparable
  return 0;
}


void f(EqualityComparable&& ec)
// template<typename T>
// void f(T&&) requires EqualityComparable<T>; // long form of the same
{
   std::cout << ec << "\n";
}
