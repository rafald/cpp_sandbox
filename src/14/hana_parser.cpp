#include <boost/hana.hpp>

#include <sstream>
#include <cassert>

using namespace boost;

template <class T>
struct parser {
  T operator()(std::istream & in) const {
    T result;
    in >> result;
    return result;
  }
};
template <typename T>
parser<T> parse() { return parser<T>(); }


struct void_ {};
struct literal_parser {
  char c;
  void_ operator()(std::istream & in) const {
    in.ignore(1, c);// do care about result, we assume it!
    return {};
  }
};
literal_parser lit(char c) { return {c}; }


template <typename ...Parsers>
auto combine_parsers(Parsers const & ... parsers) {
  return [=](std::istream & in ) {
    hana::tuple<decltype(parsers(in))...> all{parsers(in)...};//runtime call
    // remove void_ results we do not care of
    //auto result = hana::remove_if(all, [](auto presult){ return hana::typeid_(presult)==hana::typeid_(void_{}); } );
    auto result = hana::remove_if(all, [](auto presult){ return hana::typeid_(presult)==hana::type<void_>{}; } );
    return result;
  };
}

int main() {
  auto Types = hana::tuple_t<int, void, char, long, void>;
  auto NoVoid = hana::remove_if(Types, [](auto T) { return hana::traits::is_void(T); });

  auto Ptrs = hana::transform(Types, [](auto T) { return hana::traits::add_pointer(T); } );

  using namespace std::literals;
  auto tuple = hana::make_tuple(1, 2.2f, "hello"s, 3.4, 'x');
  auto no_floats = hana::remove_if(tuple, [](auto const & T) { return hana::traits::is_floating_point(hana::typeid_(T)); } );
  //TODO using refs auto const & ???
  no_floats = hana::make_tuple(1, "helo", 'x');


  /////////////////////////////////////////////////////////////////////////////

  auto parser = combine_parsers(
    lit('('), parse<int>(), lit(','), parse<std::string>(), lit(','), parse<double>(), lit(',') );
  std::istringstream text{"(1, foo, 2.)"};
  hana::tuple<int, std::string, double> data = parser(text);
  using namespace std::literals;
  assert( data == hana::make_tuple(1, "foo"s, 2.) );
}
