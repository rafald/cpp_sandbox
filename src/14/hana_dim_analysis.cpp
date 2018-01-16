#define BOOST_HANA_CONFIG_ENABLE_STRING_UDL

#include <boost/hana.hpp>

//using namespace std::literals;

#include <boost/hana/string.hpp>
namespace hana = boost::hana;
using namespace hana::literals;


int main() {
    {
        auto constexpr three = 1 + 2;
        static_assert(three == 3, "");
    }
    {
        auto three = 1_c + 2_c;
        static_assert(three == 3_c, "");
        //static_assert(std::is_same(3_c) == hana::typeid_(std::integral_constant<int,3>{}), "");
    }
    {
        constexpr auto str = "Hello world!"_s;
        //TODO why auto without constexpr is ok in the following static_assert
        auto hello_world = "hello"_s + " world"_s;
        static_assert(hello_world == "hello world"_s, "");
    }

}
