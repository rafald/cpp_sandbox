#ifndef ENUM_BIT_OP_H
#define ENUM_BIT_OP_H

// http://accu.org/index.php/journals/2228

#include <type_traits>

template <typename E>
struct enable_bitmask_operators {
   static constexpr bool enable = false;
};

template <typename E>
typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type
operator|(E lhs, E rhs) {
   typedef typename std::underlying_type<E>::type underlying;
   return static_cast<E>(static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
}

#ifdef ENUM_BIT_OP_H_EXAMPLE
enum class my_bitmask {
   first  = 1,
   second = 2,
   third  = 4
} : template <>
struct enable_bitmask_operators<my_bitmask> {
   static constexpr bool enable = true;
};
#endif

#endif  // ENUM_BIT_OP_H
