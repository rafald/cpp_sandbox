#include <iostream>

#include "runtime_get.h"

int
main() {
  std::tuple<char,char,char,char,char> t5{ 'a', 'b', 'c', 'd', 'e'};
  int i = 3;
  std::cout << runtime_get(t5, i);
  return 0;
}
