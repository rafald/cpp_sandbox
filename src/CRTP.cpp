#include <iostream>
#include <type_traits>

template <typename N, template <typename...> class... CRTPs>
class Number : public CRTPs<Number<N, CRTPs...>>... {
  public:
   // using S = std::decay_t<std::underlying_arithmetic_type_t<N>>;
   // using S = std::decay_t<std::underlying_type_t<N>>;
   using S = std::decay_t<N>;

   constexpr Number()  // note: intentionally uninitialized
   {
      check();
   }
   constexpr Number(S value) : value_(value) { check(); }

   constexpr S
   value() const {
      return value_;
   }
   constexpr void
   set_value(S a) {
      value_ = a;
   }

  private:
   static constexpr void
   check() {
      // constexpr auto is_arith = is_arithmetic<underlying_arithmetic_type_t<N>>::value;
      constexpr auto is_arith = std::is_arithmetic<S>::value;

      constexpr auto is_sl = std::is_standard_layout<Number>::value;

      static_assert(sizeof(Number) == sizeof(N), "problem with size of Number");

      static_assert(alignof(Number) == alignof(N), "problem with alignment of Number");

      static_assert(is_arith, "underlying type for Number must be arithmetic");

      static_assert(is_sl, "Number is not standard layout");
   }
   N value_;
};

////////////////////////////////////////////////////////////////////////

template <typename T>
class Stream_i {
   friend std::ostream &
   operator<<(std::ostream &a, T b) {
      return a << b.value();
   }
};

template <typename T>
class Shift_i {
   friend T
   operator<<(T a, T b) {
      return T(a.value() << b.value());
   }
   friend T
   operator>>(T a, T b) {
      return T(a.value() >> b.value());
   }
};

template <typename T>
class Eq_i {
   friend constexpr bool
   operator==(T a, T b) {
      return a.value() == b.value();
   }
   friend constexpr bool
   operator!=(T a, T b) {
      return a.value() != b.value();
   }
};

// Bit_i

////////////////////////////////////////////////////////////////////////
#if 1
template <typename T>
class write_only {
  public:
   write_only() {}
   write_only(T const &v) : m_(v) {}
   void
   operator=(T const &v) {
      m_ = v;
   }
   write_only(write_only const &) = delete;
   write_only &
   operator=(write_only const &) = delete;

  private:
   T m_;
};
// read_only
// unused
#endif
////////////////////////////////////////////////////////////////////////

int
main() {
   // using restricted_int = Number<int, Eq_i, Rel_i, Add_i, Stream_i>;
   using restricted_int = Number<int, Eq_i, Stream_i, Shift_i>;
   restricted_int ri(7);
   std::cout << ri << "\n";

   using hw_register = unsigned volatile;
   // using status_register = Number<hw_register, Bit_i>;
   using status_register = Number<hw_register, Shift_i>;
   status_register si(23);
   std::cout << (si >> 2).value() << "\n";

   return 0;
}

