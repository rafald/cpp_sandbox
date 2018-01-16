#include <boost/hana/tuple.hpp>
#include <boost/hana/integral_constant.hpp>
#include <cstddef>
#include <iostream>
// https://github.com/boostorg/hana/issues/317

namespace std
{
    template<std::size_t n, typename... Types>
    struct tuple_element<n, boost::hana::tuple<Types...>>
    {
        using type = typename decltype(+boost::hana::tuple_t<Types...>[boost::hana::size_c<n>])::type;
    };
    
    template<typename... Types>
    struct tuple_size<boost::hana::tuple<Types...>>:
        public integral_constant<std::size_t, sizeof...(Types)>
    {};
}

namespace boost
{
    namespace hana
    {
        template<std::size_t n, typename... Types>
        constexpr decltype(auto) get(hana::tuple<Types...>& t)
        {
            return t[hana::size_c<n>];
        }
        
        template<std::size_t n, typename... Types>
        constexpr decltype(auto) get(const hana::tuple<Types...>& t)
        {
            return t[hana::size_c<n>];
        }

        template<std::size_t n, typename... Types>
        constexpr decltype(auto) get(hana::tuple<Types...>&& t)
        {
            return static_cast<hana::tuple<Types...>&&>(t)[hana::size_c<n>];
        }
        
        template<std::size_t n, typename... Types>
        constexpr decltype(auto) get(const hana::tuple<Types...>&& t)
        {
            return static_cast<const hana::tuple<Types...>&&>(t)[hana::size_c<n>];
        }
    }
}


int main()
{
    auto t = boost::hana::make_tuple(1, 3.14, "Hello");
    auto& [a, b, c] = t;
    std::cout << b << std::endl; // yay
}
