//#define BOOST_HANA_CONFIG_ENABLE_STRING_UDL

#include <boost/hana.hpp>

// using namespace std::literals;

#include <boost/hana/string.hpp>
#include <boost/hana/hash.hpp>
#include <boost/hana/assert.hpp>
#include <boost/hana/at_key.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/string.hpp>

#include <vector>
#include <functional>
#include <string>
#include <iostream>

// /home/raf/develop/c++/boost_1_65_1/libs/hana/example/map/map.cpp

namespace hana = boost::hana;
//using namespace hana::literals;

auto t = hana::hash(hana::type_c<int>);
auto t2 = hana::hash(hana::type_c<double>);
auto t3 = hana::hash(hana::type_c<std::string>);

template <typename Signature>
constexpr hana::basic_type<Signature> function{};

template <char... c>
struct event {
   template <typename F>
   constexpr auto
   operator=(F f) const {
      return hana::make_pair(*this, f);
   }
};
template <typename CharT, CharT... c>
constexpr event<c...> operator""_e() {
   return {};
}
struct event_tag {};
BOOST_HANA_NAMESPACE_BEGIN
template <char ...s>
struct tag_of<event<s...>> {
    using type = event_tag;
};
template <>                               
struct equal_impl<event_tag, event_tag> {                                             
    template <typename E>                 
    static constexpr auto apply(E const&, E const&)                                     
    { return hana::true_c; }              

    template <typename E1, typename E2>   
    static constexpr auto apply(E1 const&, E2 const&)
    { return hana::false_c; }
};
template <>
struct hash_impl<event_tag> {
    template <typename Event>
    static constexpr auto apply(Event const&) {
        return hana::type_c<Event>;
    }
};
BOOST_HANA_NAMESPACE_END
auto t4 = hana::hash(event<'b', 'a', 'r'>{});

template <typename... Events>
struct event_system;
template <typename... Events, typename... Signatures>
struct event_system<hana::pair<Events, hana::basic_type<Signatures>>...> {
   hana::map<hana::pair<Events, std::vector<std::function<Signatures>>>...> map_;

   template <typename Event, typename F>
   void
   on(Event e, F callback) {
      auto is_known_event = hana::contains(map_, e);
      static_assert(is_known_event, "trying to add a callback to an unknown event");
      map_[e].push_back(callback);
   }

   template <typename Event, typename... Args>
   void
   trigger(Event e, Args... a) const {
      auto is_known_event = hana::contains(map_, e);
      static_assert(is_known_event, "trying to trigger an unknown event");
      for (auto& callback : map_[e]) callback(a...);
   }
};

template <typename... Events>
event_system<Events...>
make_event_system(Events... events) {
   return {};
}

int
main() {
   auto events = make_event_system(
       "foo"_e = function<void(std::string)>, // not std::function but empty wrapper type
       "bar"_e = function<void(int)>, 
       "baz"_e = function<void(double, int)>);

   events.on("foo"_e, [](std::string s) { std::cout << "foo with '" << s << "'!\n"; });
   events.on("foo"_e, [](std::string s) { std::cout << "foo with '" << s << "' again!\n"; });
   events.on("bar"_e, [](int i) { std::cout << "bar with '" << i << "'!\n"; });
   events.on("baz"_e, [](double d, int) { std::cout << "baz with '" << d << "'!\n"; });
   // events.on("unknown"_e, []() { }); // compiler error!

   events.trigger("foo"_e, "hello");  // no overhead for event lookup
   events.trigger("bar"_e, 4);
   events.trigger("baz"_e, 3.3, 77);
   // events.trigger("unknown"_e); // compiler error!
}