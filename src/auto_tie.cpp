#include "auto_tie.h"

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/repetition/for.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/rem.hpp>

//#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <string>
#include <tuple>
//#include <iostream>

/*
#define AUTO_TIE_HELPER1(r, data, i, elem) BOOST_PP_COMMA_IF(i) auto BOOST_PP_CAT(elem,_)
#define AUTO_TIE_HELPER2(r, data, elem) decltype( BOOST_PP_CAT(elem,_) ) elem ;

#define AUTO_TIE_IMPL(seq) auto_tie([]( BOOST_PP_SEQ_FOR_EACH_I(AUTO_TIE_HELPER1, _ , seq ) ) { \
    struct f1f067cb_03fe_47dc_a56d_93407b318d12_auto_tie_struct { BOOST_PP_SEQ_FOR_EACH(AUTO_TIE_HELPER2, _, seq) }; \
    return static_cast<f1f067cb_03fe_47dc_a56d_93407b318d12_auto_tie_struct*>(nullptr);\
})

#define AUTO_TIE(...) AUTO_TIE_IMPL(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__) )

template<class F>
struct auto_tie_helper {

    template<class T, std::size_t... I>
    auto construct(T&& t, std::index_sequence<I...>) {
        using type = std::remove_ptr_t<decltype(std::declval<F>()(std::get<I>(std::forward<T>(t))...))>;
        return type{ std::get<I>(std::forward<T>(t))... };
    }
    template<class T>
    auto operator=(T&& t) {
        return construct(std::forward<T>(t), std::make_index_sequence<std::tuple_size<std::decay_t<T>>::value>{});
    }

};

template<class F>
auto auto_tie(F f) {
    return auto_tie_helper<F>{};
}
*/

/*
namespace {

struct S {
      std::string x = "ala ma kota";
      unsigned y = 23U;
};

}

namespace std {

template<>
class tuple_size< S > :
    public integral_constant<size_t, 2>
{ };

template <size_t>
auto
get(S const & s);

TODO define std::tuple_element_t<I, S > like
std::tuple_element_t<I, std::pair<T1,T2> >
or constexpr std::variant_alternative_t<
  I, std::variant<Types...>
> const&& get(const std::variant<Types...>&& v);
}
*/
namespace {

BOOST_AUTO_TEST_CASE(test_auto_tie) {
   auto r = AUTO_TIE(x, y, z) = std::make_tuple(2, 3.3, std::string("ala ma kota"));
   BOOST_CHECK_EQUAL(r.x, 2);
   BOOST_CHECK_EQUAL(r.y, 3.3);
   BOOST_CHECK_EQUAL(r.z, std::string("ala ma kota"));
   {
      auto r = AUTO_TIE(x, y) = std::make_pair(std::string("ala ma kota"), 23U);
      BOOST_CHECK_EQUAL(r.x, std::string("ala ma kota"));
      BOOST_CHECK_EQUAL(r.y, 23U);
   }
   { /*
       auto r = AUTO_TIE(x,y) = S();
       BOOST_CHECK_EQUAL(r.x, std::string("ala ma kota"));
       BOOST_CHECK_EQUAL(r.y, 23U);*/
   }
}

}  // namespace
