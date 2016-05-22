// c++ -std=c++11 test_ct_hash.cpp && ./a.out

#include "ct_hash.h"
#include <iostream>

using namespace std;

int main() {
  using foonathan::string_id::detail::sid_hash;

  cout << sid_hash("asdas") << "\n";
  cout << sid_hash("SID") << "\n";
  cout << sid_hash("GID") << "\n";
  return 0;
}
