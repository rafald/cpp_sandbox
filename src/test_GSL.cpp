#include <functional>
#include <vector>

#define GSL_THROW_ON_CONTRACT_VIOLATION //GSL_TERMINATE_ON_CONTRACT_VIOLATION
#include "gsl/gsl"

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>


using namespace std;
using namespace gsl;

namespace n_test_owner {
void f(int* i)
{
    *i += 1;
}
BOOST_AUTO_TEST_CASE(test_owner) {
    owner<int*> p = new int(120);
    BOOST_CHECK_EQUAL(*p , 120);
    f(p);
    BOOST_CHECK_EQUAL(*p , 121);
    delete p;
}
}

namespace n_at_tests {
BOOST_AUTO_TEST_SUITE(at_tests)

    BOOST_AUTO_TEST_CASE(static_array)
    {
        int a[] = { 1, 2, 3, 4 };

        for (int i = 0; i < 4; ++i)
            BOOST_CHECK_EQUAL(at(a, i) , i+1);

        BOOST_CHECK_THROW(gsl::at(a, 4), fail_fast);
    }

    BOOST_AUTO_TEST_CASE(std_array)
    {
        std::array<int,4> a = { 1, 2, 3, 4 };

        for (int i = 0; i < 4; ++i)
            BOOST_CHECK_EQUAL(at(a, i) , i+1);

        BOOST_CHECK_THROW(at(a, 4), fail_fast);
    }

    BOOST_AUTO_TEST_CASE(StdVector)
    {
        std::vector<int> a = { 1, 2, 3, 4 };

        for (int i = 0; i < 4; ++i)
            BOOST_CHECK_EQUAL(at(a, i) , i+1);

        BOOST_CHECK_THROW(at(a, 4), fail_fast);
    }
BOOST_AUTO_TEST_SUITE_END()
}



namespace n_assertion_tests {
int f_Expects(int i)
{
	Expects(i > 0 && i < 10);
	return i;
}
int g_Ensures(int i)
{        
	i++;
	Ensures(i > 0 && i < 10);
	return i;
}
BOOST_AUTO_TEST_SUITE(assertion_tests)

    BOOST_AUTO_TEST_CASE(expects)
    {
        BOOST_CHECK_EQUAL(f_Expects(2) , 2);
        BOOST_CHECK_THROW(f_Expects(10), fail_fast);
    }


    BOOST_AUTO_TEST_CASE(ensures)
    {
        BOOST_CHECK_EQUAL(g_Ensures(2) , 3);
        BOOST_CHECK_THROW(g_Ensures(9), fail_fast);
    }
BOOST_AUTO_TEST_SUITE_END()
}



namespace n_utils_tests {
void f_utils(int& i)
{
	i += 1;
}
int j = 0;
void g_finally() { j += 1; };

BOOST_AUTO_TEST_SUITE(utils_tests)

    BOOST_AUTO_TEST_CASE(finally_lambda)
    {
        int i = 0;
        {
            auto _ = finally([&]() {f_utils(i);});
            BOOST_CHECK_EQUAL(i , 0);
        }
        BOOST_CHECK_EQUAL(i , 1);
    }

    BOOST_AUTO_TEST_CASE(finally_lambda_move)
    {
        int i = 0;
        {
            auto _1 = finally([&]() {f_utils(i);});
            {
                auto _2 = std::move(_1);
                BOOST_CHECK_EQUAL(i , 0);
            }
            BOOST_CHECK_EQUAL(i , 1);
            {
                auto _2 = std::move(_1);
                BOOST_CHECK_EQUAL(i , 1);
            }
            BOOST_CHECK_EQUAL(i , 1);
        }
        BOOST_CHECK_EQUAL(i , 1);
    }

    BOOST_AUTO_TEST_CASE(finally_function_with_bind)
    {
        int i = 0;
        {
            auto _ = finally(std::bind(&f_utils, std::ref(i)));
            BOOST_CHECK_EQUAL(i , 0);
        }
        BOOST_CHECK_EQUAL(i , 1);
    }

    BOOST_AUTO_TEST_CASE(finally_function_ptr)
    {
        j = 0;
        {
            auto _ = finally(&g_finally);
            BOOST_CHECK_EQUAL(j , 0);
        }
        BOOST_CHECK_EQUAL(j , 1);
    }

    BOOST_AUTO_TEST_CASE(test_narrow_cast)
    {
        int n = 120;
        char c = narrow_cast<char>(n);
        BOOST_CHECK_EQUAL(c , 120);

        n = 300;
        unsigned char uc = narrow_cast<unsigned char>(n);
        BOOST_CHECK_EQUAL(uc , 44);
    }

    BOOST_AUTO_TEST_CASE(test_narrow)
    {
        int n = 120;
        char c = narrow<char>(n);
        BOOST_CHECK_EQUAL(c , 120);

        n = 300;
        BOOST_CHECK_THROW(narrow<char>(n), narrowing_error);

        const auto int32_max = std::numeric_limits<int32_t>::max();
        const auto int32_min = std::numeric_limits<int32_t>::min();

        BOOST_CHECK_EQUAL(narrow<uint32_t>(int32_t(0)) , 0);
        BOOST_CHECK_EQUAL(narrow<uint32_t>(int32_t(1)) , 1);
        BOOST_CHECK_EQUAL(narrow<uint32_t>(int32_max) , int32_max);

        BOOST_CHECK_THROW(narrow<uint32_t>(int32_t(-1)), narrowing_error);
        BOOST_CHECK_THROW(narrow<uint32_t>(int32_min), narrowing_error);

        n = -42;
        BOOST_CHECK_THROW(narrow<unsigned>(n), narrowing_error);
    }
BOOST_AUTO_TEST_SUITE_END()
} //namespace n_utils_tests


namespace n_not_null {
BOOST_AUTO_TEST_SUITE(not_null_tests)
    
struct MyBase {};
struct MyDerived : public MyBase {};
struct Unrelated {};

// stand-in for a user-defined ref-counted class
template<typename T>
struct RefCounted
{
    RefCounted(T* p) : p_(p) {}
    operator T*() { return p_; }
    T* p_;
};


    bool helper(not_null<int*> p)
    {
        return *p == 12;
    }

    BOOST_AUTO_TEST_CASE(TestNotNullConstructors)
    {
#ifdef CONFIRM_COMPILATION_ERRORS
        not_null<int*> p = nullptr; // yay...does not compile!
        not_null<std::vector<char>*> p = 0; // yay...does not compile!
        not_null<int*> p; // yay...does not compile!
        std::unique_ptr<int> up = std::make_unique<int>(120);
        not_null<int*> p = up;

        // Forbid non-nullptr assignable types
        not_null<std::vector<int>> f(std::vector<int>{1});
        not_null<int> z(10);
        not_null<std::vector<int>> y({1,2});
#endif
      int i = 12; 
      auto rp = RefCounted<int>(&i);
      not_null<int*> p(rp);
      BOOST_CHECK_EQUAL(p.get() , &i);

      not_null<std::shared_ptr<int>> x(std::make_shared<int>(10)); // shared_ptr<int> is nullptr assignable
    }

    BOOST_AUTO_TEST_CASE(TestNotNullCasting)
    {
        MyBase base;
	MyDerived derived;
	Unrelated unrelated;
	not_null<Unrelated*> u = &unrelated;
        (void)u;
	not_null<MyDerived*> p = &derived;
        not_null<MyBase*> q = &base;
	q = p; // allowed with heterogeneous copy ctor
        BOOST_CHECK_EQUAL(q , p);

#ifdef CONFIRM_COMPILATION_ERRORS
	q = u; // no viable conversion possible between MyBase* and Unrelated*
	p = q; // not possible to implicitly convert MyBase* to MyDerived*

        not_null<Unrelated*> r = p;
        not_null<Unrelated*> s = reinterpret_cast<Unrelated*>(p);
#endif
        not_null<Unrelated*> t = reinterpret_cast<Unrelated*>(p.get());
        BOOST_CHECK_EQUAL((void*)p.get() , (void*)t.get());
    }

    BOOST_AUTO_TEST_CASE(TestNotNullAssignment)
    {
        int i = 12;
        not_null<int*> p = &i; 
        BOOST_CHECK(helper(p));

        int* q = nullptr;
        BOOST_CHECK_THROW(p = q, fail_fast);
    }
    
BOOST_AUTO_TEST_SUITE_END()
} 



