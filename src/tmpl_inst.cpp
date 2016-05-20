// c++ -std=c++11 tmpl_inst.cpp
#include <iostream>

//using namespace std;

namespace std {
  void
  f(int) { std::cout << "std::f int\n"; }
}

namespace oxam { 

  struct X {};

  namespace li {

  struct X {};

  template <class T>
  void
  f(T t)
  { 
    std::cout << "f master\n";
  }

} }

// !!! following f() is found if before definition of process()
// if after definition of process() not found
void
f(int) { std::cout << "::f int\n"; }

namespace util {

// looks like this shoukd be very last definition
template <class T>
void
process(T t)
{
  f(t);
}

} // util

int
main() {
  using util::process;
  process(0);

  oxam::li::X x;
  process(x);
}
