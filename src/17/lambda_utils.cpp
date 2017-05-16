// https://gist.github.com/cdacamar/584c6d43a9cca1ccffec3b36ad5dfe3f

#include <type_traits>
#include <boost/variant.hpp> //#include <variant>

#if __has_include(<algorithm>)
#include <boost/test/unit_test.hpp>
#endif


namespace std {
namespace lambda_util {

   namespace detail {

      template <typename... lambda_ts>
      struct composer_t;

      template <typename lambda_t>
      struct composer_t<lambda_t> : lambda_t {
         composer_t(const lambda_t& lambda) : lambda_t{lambda} {}
         composer_t(lambda_t&& lambda) : lambda_t{std::move(lambda)} {}

         using lambda_t::operator();
      };

      template <typename lambda_t, typename... more_lambda_ts>
      struct composer_t<lambda_t, more_lambda_ts...>
          : lambda_t
          , composer_t<more_lambda_ts...> {
         using super_t = composer_t<more_lambda_ts...>;

         template <typename... lambda_ts>
         composer_t(const lambda_t& lambda, lambda_ts&&... more_lambdas)
             : lambda_t{lambda}, super_t{std::forward<lambda_ts>(more_lambdas)...} {}
         template <typename... lambda_ts>
         composer_t(lambda_t&& lambda, lambda_ts&&... more_lambdas)
             : lambda_t{std::move(lambda)}, super_t{std::forward<lambda_ts>(more_lambdas)...} {}

         using lambda_t::operator();
         using super_t:: operator();
      };

   }  // namespace detail

   template <typename... lambda_ts>
   auto
   compose(lambda_ts&&... lambdas) {
      return detail::composer_t<std::decay_t<lambda_ts>...>{std::forward<lambda_ts>(lambdas)...};
   }

}  // namespace lambda_util

#if 0
template <class Visitor, class... Variants>
constexpr /*see below*/ decltype(auto) visit(Visitor&& vis, Variants&&... vars)
{
  return std::invoke(std::forward<Visitor>(vis), std::get<vars.index()>(std::forward<Variants>(vars))...) ;
}
#endif

}  // namespace std

BOOST_AUTO_TEST_CASE(test_lambda_util) {
   boost::variant<int, const char*, double> v;  // std::variant<int, const char*, double> v;
   v = 10.5;
   // return std::visit(lambda_util::compose([](double) { return 0; }, [](const char*) { return 1; }, [](auto) { return 2; }),
   // v);
   auto result = boost::apply_visitor(
       std::lambda_util::compose([](double) { return 3; }, [](const char*) { return 5; }, [](auto) { return 7; }), v);
   BOOST_CHECK_EQUAL(result, 3);
}

#if 0

// https://cdacamar.github.io/organization/localizing-code-with-variant/

#include <iostream>
#include <string>
#include <variant>

//#include <lambda_util>

template <typename... Ts>
void print_variant(const std::variant<Ts...>& v) {
  std::visit(
    lambda_util::compose(
      [](int i)                { std::cout<<i<<'\n';  },
      [](const std::string& s) { std::cout<<s<<'\n';  },
      [](const auto&)          { std::cout<<"TODO\n"; }),
    v);
}

void test() {
  std::variant<int, const char*, double> v;
  v = 10.5;
  auto result = std::visit(lambda_util::compose([](double) { return 0; }, [](const char*) { return 1; }, [](auto) { return 2; }), v);

  using namespace std::string_literals;
  std::variant<int, std::string> v;

  // use std::string side
  v = "Hello, World!"s;
  print_variant(v);

  // use int side
  v = 42;
  print_variant(v);
}
#endif

