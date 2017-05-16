// No main here! #define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// http://cpptruths.blogspot.com/2016/11/dependently-typed-curried-printf.html
 

#include <utility>
 
template <char... chars>
using CharSeq = std::integer_sequence<char, chars...>;
 
template <typename T, T... chars>
constexpr CharSeq<chars...> operator""_lift() {
   return {};
}

template <class Head, class Tuple>
struct Append;
 
template <class Head, class... Args>
struct Append<Head, std::tuple<Args...>> {
   using type = std::tuple<Head, Args...>;
};
 
template <class CharSeq>
struct StringToTuple;
 
template <>
struct StringToTuple<CharSeq<>> {
   using type = std::tuple<>;
};
 
template <char Any, char... chars>
struct StringToTuple<CharSeq<Any, chars...>> {
   using type = typename StringToTuple<CharSeq<chars...>>::type;
};
 
template <char... chars>
struct StringToTuple<CharSeq<'%', 's', chars...>> {
   using tail = typename StringToTuple<CharSeq<chars...>>::type;
   using type = typename Append<const char *, tail>::type;
};
 
template <char... chars>
struct StringToTuple<CharSeq<'%', 'd', chars...>> {
   using tail = typename StringToTuple<CharSeq<chars...>>::type;
   using type = typename Append<int, tail>::type;
};
 
template <char... chars>
struct StringToTuple<CharSeq<'%', 'f', chars...>> {
   using tail = typename StringToTuple<CharSeq<chars...>>::type;
   using type = typename Append<double, tail>::type;
};
 
template <char... chars>
struct StringToTuple<CharSeq<'%', 'u', chars...>> {
   using tail = typename StringToTuple<CharSeq<chars...>>::type;
   using type = typename Append<unsigned int, tail>::type;
};



 
#include <boost/core/demangle.hpp>
#include <iostream>

template <class CharSeq>
auto
curried_printf_impl(const char *fmt, CharSeq) {
   using FormatType = typename StringToTuple<CharSeq>::type;
   std::cout << boost::core::demangle(typeid(FormatType).name()) << "\n";
   return curry<FormatType>::apply(fmt);
}
 
#define curried_printf(X) curried_printf_impl(X, X##_lift)










template <class Tuple>
struct curry;

template <class Head, class... Tail>
struct curry<std::tuple<Head, Tail...>> {
   template <class... Args>
   static auto
   apply(Args &&... args) {
      return [args...](Head h) { return curry<std::tuple<Tail...>>::apply(args..., h); };
   }
};
 
template <class Head>
struct curry<std::tuple<Head>> {
   template <class... Args>
   static auto
   apply(Args &&... args) {
      return [args...](Head h) { return printf(args..., h); };
   }
};
 
template <>
struct curry<std::tuple<>> {
   static auto
   apply(const char *fmt) {
      return printf(fmt);
   }
};

// Avoiding Copying Arguments
/*
template <class Head, class... Tail>
struct curry<std::tuple<Head, Tail...>>
{
    template<class... Args>
    static auto apply(Args&&... args)
    {
      return [t=std::make_tuple(std::move(args)...)](Head h) {
          // Move each element of t and h to curry<std::tuple<Tail...>>::apply somehow.
      };
    }
};
 */

// int main()  {
BOOST_AUTO_TEST_CASE(test_ctprintf) {
   constexpr auto cpptruths = "cpptruths"_lift;
   std::cout << boost::core::demangle(typeid(decltype(cpptruths)).name()) << "\n";

   constexpr auto                        format = "%s%d"_lift;
   StringToTuple<decltype(format)>::type FormatTuple;  // std::tuple<const char *, int>

   curried_printf("C++ Rocks%s %d %f\n")("!!")(10)(20.30);
   curried_printf("C++ Rocks!!\n");
}
//}

// Currying Arbitrary Functions
#ifdef CPP_17
// In C++17, std::experimental::apply can replace the following execute function.
 
template <size_t... Indices, class Tuple, class Func>
auto
execute(std::integer_sequence<size_t, Indices...>, Tuple &&tuple, Func &&func) {
   return func(std::get<Indices>(std::forward<Tuple>(tuple))...);
}
 
template <int I, class AllArgs, class Tuple>
struct dyn_curry;
 
template <int I, class AllArgs, class Head, class... Tail>
struct dyn_curry<I, AllArgs, std::tuple<Head, Tail...>> {
   h enum { Index = std::tuple_size<AllArgs>::value - I };

   template <class Func>
   static auto
   apply(std::shared_ptr<AllArgs> shptr, Func &&func) {
      return [ shptr, func = std::move(func) ](const Head &h) mutable {
         std::get<Index>(*shptr) = h;
         return dyn_curry<I - 1, AllArgs, std::tuple<Tail...>>::apply(shptr, std::move(func));
      };
   }
};
 
template <class AllArgs, class Head>
struct dyn_curry<1, AllArgs, std::tuple<Head>> {
   enum { Index = std::tuple_size<AllArgs>::value - 1 };
   using IntSeq = std::make_index_sequence<std::tuple_size<AllArgs>::value>;

   template <class Func>
   static auto
   apply(std::shared_ptr<AllArgs> shptr, Func &&func) {
      return [ shptr, func = std::move(func) ](const Head &h) mutable {
         std::get<Index>(*shptr) = h;
         return execute(IntSeq(), sd::move(*shptr), std::move(func));
      };
   }
};
 
template <class Ret, class... Args>
auto
arb_curry(Ret (&func)(Args...)) {
   using AllArgs = std::tuple<std::decay_t<Args>...>;
   std::cout << boost::core::demangle(typeid(AllArgs).name()) << "\n";
   std::shared_ptr<AllArgs> shptr(new AllArgs);

   return dyn_curry<std::tuple_size<AllArgs>::value, AllArgs, AllArgs>::apply(shptr, func);
}
 
template <class Ret>
Ret
arb_curry(Ret (&func)()) {
   return func();
}

int
print_add(std::string &msg, int &j, int k) {
   std::cout << msg;
   return j + k;
}

int
identity(int i) {
   return i;
}

int
foo() {
   return printf("foo\n");
}

int
main(void) {
   arb_curry(foo);
   std::cout << arb_curry(identity)(99) << std::endl;
   auto a = arb_curry(print_add);
   auto b = a("Adding two integers: ");
   auto c = b(20);
   auto d = c(30);
   std::cout << d << std::endl;  // prints 60.

   return 0;
}
#endif
