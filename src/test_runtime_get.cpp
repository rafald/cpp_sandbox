// clang++-4.0 -std=c++1z

#include "runtime_get.h"

#include <iostream>


int
main() {
   std::tuple<char, char, char, char, char> t5{'a', 'b', 'c', 'd', 'e'};
   // Deduction guides: std::tuple tt5{ 'a', 'b', 'c', 'd', 'e'};
   int i = 3;
   std::cout << runtime_get(t5, i);  // tuple must be homogenious
   // std::cout << runtime_get(t5, 4);
   // std::cout << runtime_get(t5, 5);
   return 0;
}
