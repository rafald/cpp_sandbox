#include "enum_bit_op.h"

#include <iostream>

enum class my_bitmask { first = 1, second = 2, third = 4 };

template <>
struct enable_bitmask_operators<my_bitmask> {
   static constexpr bool enable = true;
};

int
main() {
   my_bitmask bm = my_bitmask::second | my_bitmask::third;
   std::cout << int(bm);
   return 0;
}
