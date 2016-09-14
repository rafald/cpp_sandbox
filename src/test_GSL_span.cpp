#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

// No main here! #define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#define GSL_THROW_ON_CONTRACT_VIOLATION // GSL_TERMINATE_ON_CONTRACT_VIOLATION
#include "span"

using namespace std;
using namespace gsl;

namespace {
struct BaseClass {};
struct DerivedClass : BaseClass {};
}

namespace n_span_tests {

BOOST_AUTO_TEST_SUITE(span_tests)

BOOST_AUTO_TEST_CASE(default_constructor) {
  {
    span<int> s;
    BOOST_CHECK(s.length() == 0 && s.data() == nullptr);

    span<const int> cs;
    BOOST_CHECK(cs.length() == 0 && cs.data() == nullptr);
  }

  {
    span<int, 0> s;
    BOOST_CHECK(s.length() == 0 && s.data() == nullptr);

    span<const int, 0> cs;
    BOOST_CHECK(cs.length() == 0 && cs.data() == nullptr);
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<int, 1> s;
    BOOST_CHECK(s.length() == 1 &&
                s.data() == nullptr); // explains why it can't compile
#endif
  }

  {
    span<int> s{};
    BOOST_CHECK(s.length() == 0 && s.data() == nullptr);

    span<const int> cs{};
    BOOST_CHECK(cs.length() == 0 && cs.data() == nullptr);
  }
}

BOOST_AUTO_TEST_CASE(from_nullptr_constructor) {
  {
    span<int> s = nullptr;
    BOOST_CHECK(s.length() == 0 && s.data() == nullptr);

    span<const int> cs = nullptr;
    BOOST_CHECK(cs.length() == 0 && cs.data() == nullptr);
  }

  {
    span<int, 0> s = nullptr;
    BOOST_CHECK(s.length() == 0 && s.data() == nullptr);

    span<const int, 0> cs = nullptr;
    BOOST_CHECK(cs.length() == 0 && cs.data() == nullptr);
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<int, 1> s = nullptr;
    BOOST_CHECK(s.length() == 1 &&
                s.data() == nullptr); // explains why it can't compile
#endif
  }

  {
    span<int> s{nullptr};
    BOOST_CHECK(s.length() == 0 && s.data() == nullptr);

    span<const int> cs{nullptr};
    BOOST_CHECK(cs.length() == 0 && cs.data() == nullptr);
  }

  {
    span<int *> s{nullptr};
    BOOST_CHECK(s.length() == 0 && s.data() == nullptr);

    span<const int *> cs{nullptr};
    BOOST_CHECK(cs.length() == 0 && cs.data() == nullptr);
  }
}

BOOST_AUTO_TEST_CASE(from_nullptr_length_constructor) {
  {
    span<int> s{nullptr, 0};
    BOOST_CHECK(s.length() == 0 && s.data() == nullptr);

    span<const int> cs{nullptr, 0};
    BOOST_CHECK(cs.length() == 0 && cs.data() == nullptr);
  }

  {
    span<int, 0> s{nullptr, 0};
    BOOST_CHECK(s.length() == 0 && s.data() == nullptr);

    span<const int, 0> cs{nullptr, 0};
    BOOST_CHECK(cs.length() == 0 && cs.data() == nullptr);
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<int, 1> s{nullptr, 0};
    BOOST_CHECK(s.length() == 1 &&
                s.data() == nullptr); // explains why it can't compile
#endif
  }

  {
    auto workaround_macro = []() { span<int> s{nullptr, 1}; };
    BOOST_CHECK_THROW(workaround_macro(), fail_fast);

    auto const_workaround_macro = []() { span<const int> cs{nullptr, 1}; };
    BOOST_CHECK_THROW(const_workaround_macro(), fail_fast);
  }

  {
    auto workaround_macro = []() { span<int, 0> s{nullptr, 1}; };
    BOOST_CHECK_THROW(workaround_macro(), fail_fast);

    auto const_workaround_macro = []() { span<const int, 0> s{nullptr, 1}; };
    BOOST_CHECK_THROW(const_workaround_macro(), fail_fast);
  }

  {
    span<int *> s{nullptr, 0};
    BOOST_CHECK(s.length() == 0 && s.data() == nullptr);

    span<const int *> cs{nullptr, 0};
    BOOST_CHECK(cs.length() == 0 && cs.data() == nullptr);
  }
}

BOOST_AUTO_TEST_CASE(from_element_constructor) {
  int i = 5;

  {
    span<int> s = i;
    BOOST_CHECK(s.length() == 1 && s.data() == &i);
    BOOST_CHECK(s[0] == 5);

    span<const int> cs = i;
    BOOST_CHECK(cs.length() == 1 && cs.data() == &i);
    BOOST_CHECK(cs[0] == 5);
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    const j = 1;
    span<int, 0> s = j;
#endif
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<int, 0> s = i;
    BOOST_CHECK(s.length() == 0 && s.data() == &i);
#endif
  }

  {
    span<int, 1> s = i;
    BOOST_CHECK(s.length() == 1 && s.data() == &i);
    BOOST_CHECK(s[0] == 5);
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<int, 2> s = i;
    BOOST_CHECK(s.length() == 2 && s.data() == &i);
#endif
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    auto get_a_temp = []() -> int { return 4; };
    auto use_a_span = [](span<int> s) { (void)s; };
    use_a_span(get_a_temp());
#endif
  }
}

BOOST_AUTO_TEST_CASE(from_pointer_length_constructor) {
  int arr[4] = {1, 2, 3, 4};

  {
    span<int> s{&arr[0], 2};
    BOOST_CHECK(s.length() == 2 && s.data() == &arr[0]);
    BOOST_CHECK(s[0] == 1 && s[1] == 2);
  }

  {
    span<int, 2> s{&arr[0], 2};
    BOOST_CHECK(s.length() == 2 && s.data() == &arr[0]);
    BOOST_CHECK(s[0] == 1 && s[1] == 2);
  }

  {
    int *p = nullptr;
    span<int> s{p, 0};
    BOOST_CHECK(s.length() == 0 && s.data() == nullptr);
  }

  {
    int *p = nullptr;
    auto workaround_macro = [=]() { span<int> s{p, 2}; };
    BOOST_CHECK_THROW(workaround_macro(), fail_fast);
  }
}

BOOST_AUTO_TEST_CASE(from_pointer_pointer_constructor) {
  int arr[4] = {1, 2, 3, 4};

  {
    span<int> s{&arr[0], &arr[2]};
    BOOST_CHECK(s.length() == 2 && s.data() == &arr[0]);
    BOOST_CHECK(s[0] == 1 && s[1] == 2);
  }

  {
    span<int, 2> s{&arr[0], &arr[2]};
    BOOST_CHECK(s.length() == 2 && s.data() == &arr[0]);
    BOOST_CHECK(s[0] == 1 && s[1] == 2);
  }

  {
    span<int> s{&arr[0], &arr[0]};
    BOOST_CHECK(s.length() == 0 && s.data() == &arr[0]);
  }

  {
    span<int, 0> s{&arr[0], &arr[0]};
    BOOST_CHECK(s.length() == 0 && s.data() == &arr[0]);
  }

  {
    auto workaround_macro = [&]() { span<int> s{&arr[1], &arr[0]}; };
    BOOST_CHECK_THROW(workaround_macro(), fail_fast);
  }

  {
    int *p = nullptr;
    auto workaround_macro = [&]() { span<int> s{&arr[0], p}; };
    BOOST_CHECK_THROW(workaround_macro(), fail_fast);
  }

  {
    int *p = nullptr;
    auto workaround_macro = [&]() { span<int> s{p, p}; };
    BOOST_CHECK_THROW(workaround_macro(), fail_fast);
  }

  {
    int *p = nullptr;
    auto workaround_macro = [&]() { span<int> s{&arr[0], p}; };
    BOOST_CHECK_THROW(workaround_macro(), fail_fast);
  }
}

BOOST_AUTO_TEST_CASE(from_array_constructor) {
  int arr[5] = {1, 2, 3, 4, 5};

  {
    span<int> s{arr};
    BOOST_CHECK(s.length() == 5 && s.data() == &arr[0]);
  }

  {
    span<int, 5> s{arr};
    BOOST_CHECK(s.length() == 5 && s.data() == &arr[0]);
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<int, 6> s{arr};
#endif
  }

  {
    span<int, 0> s{arr};
    BOOST_CHECK(s.length() == 0 && s.data() == &arr[0]);
  }

  int arr2d[2][3] = {1, 2, 3, 4, 5, 6};

  {
    span<int> s{arr2d};
    BOOST_CHECK(s.length() == 6 && s.data() == &arr2d[0][0]);
    BOOST_CHECK(s[0] == 1 && s[5] == 6);
  }

  {
    span<int, 0> s{arr2d};
    BOOST_CHECK(s.length() == 0 && s.data() == &arr2d[0][0]);
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<int, 5> s{arr2d};
#endif
  }

  {
    span<int, 6> s{arr2d};
    BOOST_CHECK(s.length() == 6 && s.data() == &arr2d[0][0]);
    BOOST_CHECK(s[0] == 1 && s[5] == 6);
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<int, 7> s{arr2d};
#endif
  }

  {
    span<int[3]> s{arr2d[0]};
    BOOST_CHECK(s.length() == 1 && s.data() == &arr2d[0]);
  }

  {
    span<int, 2, 3> s{arr2d};
    BOOST_CHECK(s.length() == 6 && s.data() == &arr2d[0][0]);
    auto workaround_macro = [&]() { return s[{1, 2}] == 6; };
    BOOST_CHECK(workaround_macro());
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<int, 3, 3> s{arr2d};
#endif
  }

  int arr3d[2][3][2] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  {
    span<int> s{arr3d};
    BOOST_CHECK(s.length() == 12 && s.data() == &arr3d[0][0][0]);
    BOOST_CHECK(s[0] == 1 && s[11] == 12);
  }

  {
    span<int, 0> s{arr3d};
    BOOST_CHECK(s.length() == 0 && s.data() == &arr3d[0][0][0]);
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<int, 11> s{arr3d};
#endif
  }

  {
    span<int, 12> s{arr3d};
    BOOST_CHECK(s.length() == 12 && s.data() == &arr3d[0][0][0]);
    BOOST_CHECK(s[0] == 1 && s[5] == 6);
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<int, 13> s{arr3d};
#endif
  }

  {
    span<int[3][2]> s{arr3d[0]};
    BOOST_CHECK(s.length() == 1 && s.data() == &arr3d[0]);
  }

  {
    span<int, 3, 2, 2> s{arr3d};
    BOOST_CHECK(s.length() == 12 && s.data() == &arr3d[0][0][0]);
    auto workaround_macro = [&]() { return s[{2, 1, 0}] == 11; };
    BOOST_CHECK(workaround_macro());
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<int, 3, 3, 3> s{arr3d};
#endif
  }
}

BOOST_AUTO_TEST_CASE(from_dynamic_array_constructor) {
  double(*arr)[3][4] = new double[100][3][4];

  {
    span<double, dynamic_range, 3, 4> s(arr, 10);
    BOOST_CHECK(s.length() == 120 && s.data() == &arr[0][0][0]);
    BOOST_CHECK_THROW(s[10][3][4], fail_fast);
  }

  {
    span<double, dynamic_range, 4, 3> s(arr, 10);
    BOOST_CHECK(s.length() == 120 && s.data() == &arr[0][0][0]);
  }

  {
    span<double> s(arr, 10);
    BOOST_CHECK(s.length() == 120 && s.data() == &arr[0][0][0]);
  }

  {
    span<double, dynamic_range, 3, 4> s(arr, 0);
    BOOST_CHECK(s.length() == 0 && s.data() == &arr[0][0][0]);
  }

  delete[] arr;
}

BOOST_AUTO_TEST_CASE(from_std_array_constructor) {
  std::array<int, 4> arr = {1, 2, 3, 4};

  {
    span<int> s{arr};
    BOOST_CHECK(s.size() == narrow_cast<ptrdiff_t>(arr.size()) &&
                s.data() == arr.data());

    span<const int> cs{arr};
    BOOST_CHECK(cs.size() == narrow_cast<ptrdiff_t>(arr.size()) &&
                cs.data() == arr.data());
  }

  {
    span<int, 4> s{arr};
    BOOST_CHECK(s.size() == narrow_cast<ptrdiff_t>(arr.size()) &&
                s.data() == arr.data());

    span<const int, 4> cs{arr};
    BOOST_CHECK(cs.size() == narrow_cast<ptrdiff_t>(arr.size()) &&
                cs.data() == arr.data());
  }

  {
    span<int, 2> s{arr};
    BOOST_CHECK(s.size() == 2 && s.data() == arr.data());

    span<const int, 2> cs{arr};
    BOOST_CHECK(cs.size() == 2 && cs.data() == arr.data());
  }

  {
    span<int, 0> s{arr};
    BOOST_CHECK(s.size() == 0 && s.data() == arr.data());

    span<const int, 0> cs{arr};
    BOOST_CHECK(cs.size() == 0 && cs.data() == arr.data());
  }

  // TODO This is currently an unsupported scenario. We will come back to it as
  // we revise
  // the multidimensional interface and what transformations between
  // dimensionality look like
  //{
  //    span<int, 2, 2> s{arr};
  //    BOOST_CHECK(s.size() == narrow_cast<ptrdiff_t>(arr.size()) && s.data()
  //    == arr.data());
  //}

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<int, 5> s{arr};
#endif
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    auto get_an_array = []() { return std::array<int, 4>{1, 2, 3, 4}; };
    auto take_a_span = [](span<int> s) { (void)s; };
    // try to take a temporary std::array
    take_a_span(get_an_array());
#endif
  }
}

BOOST_AUTO_TEST_CASE(from_const_std_array_constructor) {
  const std::array<int, 4> arr = {1, 2, 3, 4};

  {
    span<const int> s{arr};
    BOOST_CHECK(s.size() == narrow_cast<ptrdiff_t>(arr.size()) &&
                s.data() == arr.data());
  }

  {
    span<const int, 4> s{arr};
    BOOST_CHECK(s.size() == narrow_cast<ptrdiff_t>(arr.size()) &&
                s.data() == arr.data());
  }

  {
    span<const int, 2> s{arr};
    BOOST_CHECK(s.size() == 2 && s.data() == arr.data());
  }

  {
    span<const int, 0> s{arr};
    BOOST_CHECK(s.size() == 0 && s.data() == arr.data());
  }

  // TODO This is currently an unsupported scenario. We will come back to it as
  // we revise
  // the multidimensional interface and what transformations between
  // dimensionality look like
  //{
  //    span<int, 2, 2> s{arr};
  //    BOOST_CHECK(s.size() == narrow_cast<ptrdiff_t>(arr.size()) && s.data()
  //    == arr.data());
  //}

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<const int, 5> s{arr};
#endif
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    auto get_an_array = []() -> const std::array<int, 4> {
      return {1, 2, 3, 4};
    };
    auto take_a_span = [](span<const int> s) { (void)s; };
    // try to take a temporary std::array
    take_a_span(get_an_array());
#endif
  }
}

BOOST_AUTO_TEST_CASE(from_container_constructor) {
  std::vector<int> v = {1, 2, 3};
  const std::vector<int> cv = v;

  {
    span<int> s{v};
    BOOST_CHECK(s.size() == narrow_cast<std::ptrdiff_t>(v.size()) &&
                s.data() == v.data());

    span<const int> cs{v};
    BOOST_CHECK(cs.size() == narrow_cast<std::ptrdiff_t>(v.size()) &&
                cs.data() == v.data());
  }

  std::string str = "hello";
  const std::string cstr = "hello";

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<char> s{str};
    BOOST_CHECK(s.size() == narrow_cast<std::ptrdiff_t>(str.size()) &&
                s.data() == str.data());
#endif
    span<const char> cs{str};
    BOOST_CHECK(cs.size() == narrow_cast<std::ptrdiff_t>(str.size()) &&
                cs.data() == str.data());
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    span<char> s{cstr};
#endif
    span<const char> cs{cstr};
    BOOST_CHECK(cs.size() == narrow_cast<std::ptrdiff_t>(cstr.size()) &&
                cs.data() == cstr.data());
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    auto get_temp_vector = []() -> std::vector<int> { return {}; };
    auto use_span = [](span<int> s) { (void)s; };
    use_span(get_temp_vector());
#endif
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    auto get_temp_string = []() -> std::string { return {}; };
    auto use_span = [](span<char> s) { (void)s; };
    use_span(get_temp_string());
#endif
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    auto get_temp_vector = []() -> const std::vector<int> { return {}; };
    auto use_span = [](span<const char> s) { (void)s; };
    use_span(get_temp_vector());
#endif
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    auto get_temp_string = []() -> const std::string { return {}; };
    auto use_span = [](span<const char> s) { (void)s; };
    use_span(get_temp_string());
#endif
  }

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    std::map<int, int> m;
    span<int> s{m};
#endif
  }
}

BOOST_AUTO_TEST_CASE(from_convertible_span_constructor) {
#ifdef CONFIRM_COMPILATION_ERRORS
  span<int, 7, 4, 2> av1(nullptr, b1);

  auto f = [&]() { span<int, 7, 4, 2> av1(nullptr); };
  BOOST_CHECK_THROW(f(), fail_fast);
#endif

#ifdef CONFIRM_COMPILATION_ERRORS
  static_bounds<size_t, 7, dynamic_range, 2> b12(b11);
  b12 = b11;
  b11 = b12;

  span<int, dynamic_range> av1 = nullptr;
  span<int, 7, dynamic_range, 2> av2(av1);
  span<int, 7, 4, 2> av2(av1);
#endif

  span<DerivedClass> avd;
#ifdef CONFIRM_COMPILATION_ERRORS
  span<BaseClass> avb = avd;
#endif
  span<const DerivedClass> avcd = avd;
  (void)avcd;
}

BOOST_AUTO_TEST_CASE(copy_move_and_assignment) {
  span<int> s1;
  BOOST_CHECK(s1.empty());

  int arr[] = {3, 4, 5};

  span<const int> s2 = arr;
  BOOST_CHECK(s2.length() == 3 && s2.data() == &arr[0]);

  s2 = s1;
  BOOST_CHECK(s2.empty());

  auto get_temp_span = [&]() -> span<int> { return {&arr[1], 2}; };
  auto use_span = [&](span<const int> s) {
    BOOST_CHECK(s.length() == 2 && s.data() == &arr[1]);
  };
  use_span(get_temp_span());

  s1 = get_temp_span();
  BOOST_CHECK(s1.length() == 2 && s1.data() == &arr[1]);
}

template <class Bounds> void fn(const Bounds &) {
  static_assert(Bounds::static_size == 60, "static bounds is wrong size");
}
BOOST_AUTO_TEST_CASE(as_span_reshape) {
  int a[3][4][5];
  auto av = as_span(a);
  fn(av.bounds());
  auto av2 = as_span(av, dim<60>());
  auto av3 = as_span(av2, dim<3>(), dim<4>(), dim<5>());
  auto av4 = as_span(av3, dim<4>(), dim<>(3), dim<5>());
  auto av5 = as_span(av4, dim<3>(), dim<4>(), dim<5>());
  auto av6 = as_span(av5, dim<12>(), dim<>(5));

  fill(av6.begin(), av6.end(), 1);

  auto av7 = as_bytes(av6);

  auto av8 = as_span<int>(av7);

  BOOST_CHECK(av8.size() == av6.size());
  for (auto i = 0; i < av8.size(); i++) {
    BOOST_CHECK(av8[i] == 1);
  }
}

BOOST_AUTO_TEST_CASE(first) {
  int arr[5] = {1, 2, 3, 4, 5};

  {
    span<int, 5> av = arr;
    BOOST_CHECK((av.first<2>().bounds() == static_bounds<2>()));
    BOOST_CHECK(av.first<2>().length() == 2);
    BOOST_CHECK(av.first(2).length() == 2);
  }

  {
    span<int, 5> av = arr;
    BOOST_CHECK((av.first<0>().bounds() == static_bounds<0>()));
    BOOST_CHECK(av.first<0>().length() == 0);
    BOOST_CHECK(av.first(0).length() == 0);
  }

  {
    span<int, 5> av = arr;
    BOOST_CHECK((av.first<5>().bounds() == static_bounds<5>()));
    BOOST_CHECK(av.first<5>().length() == 5);
    BOOST_CHECK(av.first(5).length() == 5);
  }

  {
    span<int, 5> av = arr;
#ifdef CONFIRM_COMPILATION_ERRORS
    BOOST_CHECK(av.first<6>().bounds() == static_bounds<6>());
    BOOST_CHECK(av.first<6>().length() == 6);
    BOOST_CHECK(av.first<-1>().length() == -1);
#endif
    BOOST_CHECK_THROW(av.first(6).length(), fail_fast);
  }

  {
    span<int, dynamic_range> av;
    BOOST_CHECK((av.first<0>().bounds() == static_bounds<0>()));
    BOOST_CHECK(av.first<0>().length() == 0);
    BOOST_CHECK(av.first(0).length() == 0);
  }
}

BOOST_AUTO_TEST_CASE(last) {
  int arr[5] = {1, 2, 3, 4, 5};

  {
    span<int, 5> av = arr;
    BOOST_CHECK((av.last<2>().bounds() == static_bounds<2>()));
    BOOST_CHECK(av.last<2>().length() == 2);
    BOOST_CHECK(av.last(2).length() == 2);
  }

  {
    span<int, 5> av = arr;
    BOOST_CHECK((av.last<0>().bounds() == static_bounds<0>()));
    BOOST_CHECK(av.last<0>().length() == 0);
    BOOST_CHECK(av.last(0).length() == 0);
  }

  {
    span<int, 5> av = arr;
    BOOST_CHECK((av.last<5>().bounds() == static_bounds<5>()));
    BOOST_CHECK(av.last<5>().length() == 5);
    BOOST_CHECK(av.last(5).length() == 5);
  }

  {
    span<int, 5> av = arr;
#ifdef CONFIRM_COMPILATION_ERRORS
    BOOST_CHECK((av.last<6>().bounds() == static_bounds<6>()));
    BOOST_CHECK(av.last<6>().length() == 6);
#endif
    BOOST_CHECK_THROW(av.last(6).length(), fail_fast);
  }

  {
    span<int, dynamic_range> av;
    BOOST_CHECK((av.last<0>().bounds() == static_bounds<0>()));
    BOOST_CHECK(av.last<0>().length() == 0);
    BOOST_CHECK(av.last(0).length() == 0);
  }
}

BOOST_AUTO_TEST_CASE(subspan) {
  int arr[5] = {1, 2, 3, 4, 5};

  {
    span<int, 5> av = arr;
    BOOST_CHECK((av.subspan<2, 2>().bounds() == static_bounds<2>()));
    BOOST_CHECK((av.subspan<2, 2>().length() == 2));
    BOOST_CHECK(av.subspan(2, 2).length() == 2);
    BOOST_CHECK(av.subspan(2, 3).length() == 3);
  }

  {
    span<int, 5> av = arr;
    BOOST_CHECK((av.subspan<0, 0>().bounds() == static_bounds<0>()));
    BOOST_CHECK((av.subspan<0, 0>().length() == 0));
    BOOST_CHECK(av.subspan(0, 0).length() == 0);
  }

  {
    span<int, 5> av = arr;
    BOOST_CHECK((av.subspan<0, 5>().bounds() == static_bounds<5>()));
    BOOST_CHECK((av.subspan<0, 5>().length() == 5));
    BOOST_CHECK(av.subspan(0, 5).length() == 5);
    BOOST_CHECK_THROW(av.subspan(0, 6).length(), fail_fast);
    BOOST_CHECK_THROW(av.subspan(1, 5).length(), fail_fast);
  }

  {
    span<int, 5> av = arr;
    BOOST_CHECK((av.subspan<5, 0>().bounds() == static_bounds<0>()));
    BOOST_CHECK((av.subspan<5, 0>().length() == 0));
    BOOST_CHECK(av.subspan(5, 0).length() == 0);
    BOOST_CHECK_THROW(av.subspan(6, 0).length(), fail_fast);
  }

  {
    span<int, dynamic_range> av;
    BOOST_CHECK((av.subspan<0, 0>().bounds() == static_bounds<0>()));
    BOOST_CHECK((av.subspan<0, 0>().length() == 0));
    BOOST_CHECK(av.subspan(0, 0).length() == 0);
    BOOST_CHECK_THROW((av.subspan<1, 0>().length()), fail_fast);
  }

  {
    span<int> av;
    BOOST_CHECK(av.subspan(0).length() == 0);
    BOOST_CHECK_THROW(av.subspan(1).length(), fail_fast);
  }

  {
    span<int> av = arr;
    BOOST_CHECK(av.subspan(0).length() == 5);
    BOOST_CHECK(av.subspan(1).length() == 4);
    BOOST_CHECK(av.subspan(4).length() == 1);
    BOOST_CHECK(av.subspan(5).length() == 0);
    BOOST_CHECK_THROW(av.subspan(6).length(), fail_fast);
    auto av2 = av.subspan(1);
    for (int i = 0; i < 4; ++i)
      BOOST_CHECK(av2[i] == i + 2);
  }

  {
    span<int, 5> av = arr;
    BOOST_CHECK(av.subspan(0).length() == 5);
    BOOST_CHECK(av.subspan(1).length() == 4);
    BOOST_CHECK(av.subspan(4).length() == 1);
    BOOST_CHECK(av.subspan(5).length() == 0);
    BOOST_CHECK_THROW(av.subspan(6).length(), fail_fast);
    auto av2 = av.subspan(1);
    for (int i = 0; i < 4; ++i)
      BOOST_CHECK(av2[i] == i + 2);
  }
}

BOOST_AUTO_TEST_CASE(rank) {
  int arr[2] = {1, 2};

  {
    span<int> s;
    BOOST_CHECK(s.rank() == 1);
  }

  {
    span<int, 2> s = arr;
    BOOST_CHECK(s.rank() == 1);
  }

  int arr2d[1][1] = {};
  {
    span<int, 1, 1> s = arr2d;
    BOOST_CHECK(s.rank() == 2);
  }
}

BOOST_AUTO_TEST_CASE(extent) {
  {
    span<int> s;
    BOOST_CHECK(s.extent() == 0);
    BOOST_CHECK(s.extent(0) == 0);
    BOOST_CHECK_THROW(s.extent(1), fail_fast);
#ifdef CONFIRM_COMPILATION_ERRORS
    BOOST_CHECK(s.extent<1>() == 0);
#endif
  }

  {
    span<int, 0> s;
    BOOST_CHECK(s.extent() == 0);
    BOOST_CHECK(s.extent(0) == 0);
    BOOST_CHECK_THROW(s.extent(1), fail_fast);
  }

  {
    int arr2d[1][2] = {};

    span<int, 1, 2> s = arr2d;
    BOOST_CHECK(s.extent() == 1);
    BOOST_CHECK(s.extent<0>() == 1);
    BOOST_CHECK(s.extent<1>() == 2);
    BOOST_CHECK(s.extent(0) == 1);
    BOOST_CHECK(s.extent(1) == 2);
    BOOST_CHECK_THROW(s.extent(3), fail_fast);
  }

  {
    int arr2d[1][2] = {};

    span<int, 0, 2> s = arr2d;
    BOOST_CHECK(s.extent() == 0);
    BOOST_CHECK(s.extent<0>() == 0);
    BOOST_CHECK(s.extent<1>() == 2);
    BOOST_CHECK(s.extent(0) == 0);
    BOOST_CHECK(s.extent(1) == 2);
    BOOST_CHECK_THROW(s.extent(3), fail_fast);
  }
}

BOOST_AUTO_TEST_CASE(operator_function_call) {
  int arr[4] = {1, 2, 3, 4};

  {
    span<int> s = arr;
    BOOST_CHECK(s(0) == 1);
    BOOST_CHECK_THROW(s(5), fail_fast);
  }

  int arr2d[2][3] = {1, 2, 3, 4, 5, 6};

  {
    span<int, 2, 3> s = arr2d;
    BOOST_CHECK(s(0, 0) == 1);
    BOOST_CHECK(s(1, 2) == 6);
  }
}

BOOST_AUTO_TEST_CASE(comparison_operators) {
  {
    int arr[10][2];
    auto s1 = as_span(arr);
    span<const int, dynamic_range, 2> s2 = s1;

    BOOST_CHECK(s1 == s2);

    span<int, 20> s3 = as_span(s1, dim<>(20));
    BOOST_CHECK(s3 == s2 && s3 == s1);
  }

  {
    auto s1 = nullptr;
    auto s2 = nullptr;
    BOOST_CHECK(s1 == s2);
    BOOST_CHECK(!(s1 != s2));
    BOOST_CHECK(!(s1 < s2));
    BOOST_CHECK(s1 <= s2);
    BOOST_CHECK(!(s1 > s2));
    BOOST_CHECK(s1 >= s2);
    BOOST_CHECK(s2 == s1);
    BOOST_CHECK(!(s2 != s1));
    BOOST_CHECK(!(s2 < s1));
    BOOST_CHECK(s2 <= s1);
    BOOST_CHECK(!(s2 > s1));
    BOOST_CHECK(s2 >= s1);
  }

  {
    int arr[] = {2, 1}; // bigger

    span<int> s1 = nullptr;
    span<int> s2 = arr;

    BOOST_CHECK(s1 != s2);
    BOOST_CHECK(s2 != s1);
    BOOST_CHECK(!(s1 == s2));
    BOOST_CHECK(!(s2 == s1));
    BOOST_CHECK(s1 < s2);
    BOOST_CHECK(!(s2 < s1));
    BOOST_CHECK(s1 <= s2);
    BOOST_CHECK(!(s2 <= s1));
    BOOST_CHECK(s2 > s1);
    BOOST_CHECK(!(s1 > s2));
    BOOST_CHECK(s2 >= s1);
    BOOST_CHECK(!(s1 >= s2));
  }

  {
    int arr1[] = {1, 2};
    int arr2[] = {1, 2};
    span<int> s1 = arr1;
    span<int> s2 = arr2;

    BOOST_CHECK(s1 == s2);
    BOOST_CHECK(!(s1 != s2));
    BOOST_CHECK(!(s1 < s2));
    BOOST_CHECK(s1 <= s2);
    BOOST_CHECK(!(s1 > s2));
    BOOST_CHECK(s1 >= s2);
    BOOST_CHECK(s2 == s1);
    BOOST_CHECK(!(s2 != s1));
    BOOST_CHECK(!(s2 < s1));
    BOOST_CHECK(s2 <= s1);
    BOOST_CHECK(!(s2 > s1));
    BOOST_CHECK(s2 >= s1);
  }

  {
    int arr[] = {1, 2, 3};

    span<int> s1 = {&arr[0], 2}; // shorter
    span<int> s2 = arr;          // longer

    BOOST_CHECK(s1 != s2);
    BOOST_CHECK(s2 != s1);
    BOOST_CHECK(!(s1 == s2));
    BOOST_CHECK(!(s2 == s1));
    BOOST_CHECK(s1 < s2);
    BOOST_CHECK(!(s2 < s1));
    BOOST_CHECK(s1 <= s2);
    BOOST_CHECK(!(s2 <= s1));
    BOOST_CHECK(s2 > s1);
    BOOST_CHECK(!(s1 > s2));
    BOOST_CHECK(s2 >= s1);
    BOOST_CHECK(!(s1 >= s2));
  }

  {
    int arr1[] = {1, 2}; // smaller
    int arr2[] = {2, 1}; // bigger

    span<int> s1 = arr1;
    span<int> s2 = arr2;

    BOOST_CHECK(s1 != s2);
    BOOST_CHECK(s2 != s1);
    BOOST_CHECK(!(s1 == s2));
    BOOST_CHECK(!(s2 == s1));
    BOOST_CHECK(s1 < s2);
    BOOST_CHECK(!(s2 < s1));
    BOOST_CHECK(s1 <= s2);
    BOOST_CHECK(!(s2 <= s1));
    BOOST_CHECK(s2 > s1);
    BOOST_CHECK(!(s1 > s2));
    BOOST_CHECK(s2 >= s1);
    BOOST_CHECK(!(s1 >= s2));
  }
}

BOOST_AUTO_TEST_CASE(basics) {
  auto ptr = as_span(new int[10], 10);
  fill(ptr.begin(), ptr.end(), 99);
  for (int num : ptr) {
    BOOST_CHECK(num == 99);
  }

  delete[] ptr.data();
}

BOOST_AUTO_TEST_CASE(bounds_checks) {
  int arr[10][2];
  auto av = as_span(arr);

  fill(begin(av), end(av), 0);

  av[2][0] = 1;
  av[1][1] = 3;

  // out of bounds
  BOOST_CHECK_THROW(av[1][3] = 3, fail_fast);
  BOOST_CHECK_THROW((av[{1, 3}] = 3), fail_fast);

  BOOST_CHECK_THROW(av[10][2], fail_fast);
  BOOST_CHECK_THROW((av[{10, 2}]), fail_fast);
}

void overloaded_func(span<const int, dynamic_range, 3, 5> exp,
                     int expected_value) {
  for (auto val : exp) {
    BOOST_CHECK(val == expected_value);
  }
}

void overloaded_func(span<const char, dynamic_range, 3, 5> exp,
                     char expected_value) {
  for (auto val : exp) {
    BOOST_CHECK(val == expected_value);
  }
}

void fixed_func(span<int, 3, 3, 5> exp, int expected_value) {
  for (auto val : exp) {
    BOOST_CHECK(val == expected_value);
  }
}

BOOST_AUTO_TEST_CASE(span_parameter_test) {
  auto data = new int[4][3][5];

  auto av = as_span(data, 4);

  BOOST_CHECK(av.size() == 60);

  fill(av.begin(), av.end(), 34);

  int count = 0;
  for_each(av.rbegin(), av.rend(), [&](int val) { count += val; });
  BOOST_CHECK(count == 34 * 60);
  overloaded_func(av, 34);

  overloaded_func(as_span(av, dim<>(4), dim<>(3), dim<>(5)), 34);

  // fixed_func(av, 34);
  delete[] data;
}

BOOST_AUTO_TEST_CASE(md_access) {
  auto width = 5, height = 20;

  auto imgSize = width * height;
  auto image_ptr = new int[imgSize][3];

  // size check will be done
  auto image_view = as_span(as_span(image_ptr, imgSize), dim<>(height),
                            dim<>(width), dim<3>());

  iota(image_view.begin(), image_view.end(), 1);

  int expected = 0;
  for (auto i = 0; i < height; i++) {
    for (auto j = 0; j < width; j++) {
      BOOST_CHECK(expected + 1 == image_view[i][j][0]);
      BOOST_CHECK(expected + 2 == image_view[i][j][1]);
      BOOST_CHECK(expected + 3 == image_view[i][j][2]);

      auto val = image_view[{i, j, 0}];
      BOOST_CHECK(expected + 1 == val);
      val = image_view[{i, j, 1}];
      BOOST_CHECK(expected + 2 == val);
      val = image_view[{i, j, 2}];
      BOOST_CHECK(expected + 3 == val);

      expected += 3;
    }
  }
}

BOOST_AUTO_TEST_CASE(TEST_as_span) {
  {
    int *arr = new int[150];

    auto av = as_span(arr, dim<10>(), dim<>(3), dim<5>());

    fill(av.begin(), av.end(), 24);
    overloaded_func(av, 24);

    delete[] arr;

    array<int, 15> stdarr{0};
    auto av2 = as_span(stdarr);
    overloaded_func(as_span(av2, dim<>(1), dim<3>(), dim<5>()), 0);

    string str = "ttttttttttttttt"; // size = 15
    auto t = str.data();
    (void)t;
    auto av3 = as_span(str);
    overloaded_func(as_span(av3, dim<>(1), dim<3>(), dim<5>()), 't');
  }

  {
    string str;
    span<char> strspan = as_span(str);
    (void)strspan;
    const string cstr;
    span<const char> cstrspan = as_span(cstr);
    (void)cstrspan;
  }

  {
    int a[3][4][5];
    auto av = as_span(a);
    const int(*b)[4][5];
    b = a;
    auto bv = as_span(b, 3);

    BOOST_CHECK(av == bv);

    const std::array<double, 3> arr = {0.0, 0.0, 0.0};
    auto cv = as_span(arr);
    (void)cv;

    vector<float> vec(3);
    auto dv = as_span(vec);
    (void)dv;

#ifdef CONFIRM_COMPILATION_ERRORS
    auto dv2 = as_span(std::move(vec));
#endif
  }
}

BOOST_AUTO_TEST_CASE(empty_spans) {
  {
    span<int, 0> empty_av(nullptr);

    BOOST_CHECK(empty_av.bounds().index_bounds() == gsl::index<1>{0});
    BOOST_CHECK_THROW(empty_av[0], fail_fast);
    BOOST_CHECK_THROW(empty_av.begin()[0], fail_fast);
    BOOST_CHECK_THROW(empty_av.cbegin()[0], fail_fast);
    for (auto &v : empty_av) {
      (void)v;
      BOOST_CHECK(false);
    }
  }

  {
    span<int> empty_av = {};
    BOOST_CHECK(empty_av.bounds().index_bounds() == gsl::index<1>{0});
    BOOST_CHECK_THROW(empty_av[0], fail_fast);
    BOOST_CHECK_THROW(empty_av.begin()[0], fail_fast);
    BOOST_CHECK_THROW(empty_av.cbegin()[0], fail_fast);
    for (auto &v : empty_av) {
      (void)v;
      BOOST_CHECK(false);
    }
  }
}

BOOST_AUTO_TEST_CASE(index_constructor) {
  auto arr = new int[8];
  for (int i = 0; i < 4; ++i) {
    arr[2 * i] = 4 + i;
    arr[2 * i + 1] = i;
  }

  span<int, dynamic_range> av(arr, 8);

  ptrdiff_t a[1] = {0};
  gsl::index<1> i = a;

  BOOST_CHECK(av[i] == 4);

  auto av2 = as_span(av, dim<4>(), dim<>(2));
  ptrdiff_t a2[2] = {0, 1};
  gsl::index<2> i2 = a2;

  BOOST_CHECK(av2[i2] == 0);
  BOOST_CHECK(av2[0][i] == 4);

  delete[] arr;
}

BOOST_AUTO_TEST_CASE(index_constructors) {
  {
    // components of the same type
    gsl::index<3> i1(0, 1, 2);
    BOOST_CHECK(i1[0] == 0);

    // components of different types
    size_t c0 = 0;
    size_t c1 = 1;
    gsl::index<3> i2(c0, c1, 2);
    BOOST_CHECK(i2[0] == 0);

    // from array
    gsl::index<3> i3 = {0, 1, 2};
    BOOST_CHECK(i3[0] == 0);

    // from other gsl::index of the same size type
    gsl::index<3> i4 = i3;
    BOOST_CHECK(i4[0] == 0);

    // default
    gsl::index<3> i7;
    BOOST_CHECK(i7[0] == 0);

    // default
    gsl::index<3> i9 = {};
    BOOST_CHECK(i9[0] == 0);
  }

  {
    // components of the same type
    gsl::index<1> i1(0);
    BOOST_CHECK(i1[0] == 0);

    // components of different types
    size_t c0 = 0;
    gsl::index<1> i2(c0);
    BOOST_CHECK(i2[0] == 0);

    // from array
    gsl::index<1> i3 = {0};
    BOOST_CHECK(i3[0] == 0);

    // from int
    gsl::index<1> i4 = 0;
    BOOST_CHECK(i4[0] == 0);

    // from other gsl::index of the same size type
    gsl::index<1> i5 = i3;
    BOOST_CHECK(i5[0] == 0);

    // default
    gsl::index<1> i8;
    BOOST_CHECK(i8[0] == 0);

    // default
    gsl::index<1> i9 = {};
    BOOST_CHECK(i9[0] == 0);
  }

#ifdef CONFIRM_COMPILATION_ERRORS
  {
    gsl::index<3> i1(0, 1);
    gsl::index<3> i2(0, 1, 2, 3);
    gsl::index<3> i3 = {0};
    gsl::index<3> i4 = {0, 1, 2, 3};
    gsl::index<1> i5 = {0, 1};
  }
#endif
}

BOOST_AUTO_TEST_CASE(index_operations) {
  ptrdiff_t a[3] = {0, 1, 2};
  ptrdiff_t b[3] = {3, 4, 5};
  gsl::index<3> i = a;
  gsl::index<3> j = b;

  BOOST_CHECK(i[0] == 0);
  BOOST_CHECK(i[1] == 1);
  BOOST_CHECK(i[2] == 2);

  {
    gsl::index<3> k = i + j;

    BOOST_CHECK(i[0] == 0);
    BOOST_CHECK(i[1] == 1);
    BOOST_CHECK(i[2] == 2);
    BOOST_CHECK(k[0] == 3);
    BOOST_CHECK(k[1] == 5);
    BOOST_CHECK(k[2] == 7);
  }

  {
    gsl::index<3> k = i * 3;

    BOOST_CHECK(i[0] == 0);
    BOOST_CHECK(i[1] == 1);
    BOOST_CHECK(i[2] == 2);
    BOOST_CHECK(k[0] == 0);
    BOOST_CHECK(k[1] == 3);
    BOOST_CHECK(k[2] == 6);
  }

  {
    gsl::index<3> k = 3 * i;

    BOOST_CHECK(i[0] == 0);
    BOOST_CHECK(i[1] == 1);
    BOOST_CHECK(i[2] == 2);
    BOOST_CHECK(k[0] == 0);
    BOOST_CHECK(k[1] == 3);
    BOOST_CHECK(k[2] == 6);
  }

  {
    gsl::index<2> k = details::shift_left(i);

    BOOST_CHECK(i[0] == 0);
    BOOST_CHECK(i[1] == 1);
    BOOST_CHECK(i[2] == 2);
    BOOST_CHECK(k[0] == 1);
    BOOST_CHECK(k[1] == 2);
  }
}

void iterate_second_column(span<int, dynamic_range, dynamic_range> av) {
  auto length = av.size() / 2;

  // view to the second column
  auto section = av.section({0, 1}, {length, 1});

  BOOST_CHECK(section.size() == length);
  for (auto i = 0; i < section.size(); ++i) {
    BOOST_CHECK(section[i][0] == av[i][1]);
  }

  for (auto i = 0; i < section.size(); ++i) {
    auto idx = gsl::index<2>{i, 0}; // avoid braces inside the BOOST_CHECK macro
    BOOST_CHECK(section[idx] == av[i][1]);
  }

  BOOST_CHECK(section.bounds().index_bounds()[0] == length);
  BOOST_CHECK(section.bounds().index_bounds()[1] == 1);
  for (auto i = 0; i < section.bounds().index_bounds()[0]; ++i) {
    for (auto j = 0; j < section.bounds().index_bounds()[1]; ++j) {
      auto idx =
          gsl::index<2>{i, j}; // avoid braces inside the BOOST_CHECK macro
      BOOST_CHECK(section[idx] == av[i][1]);
    }
  }

  size_t check_sum = 0;
  for (auto i = 0; i < length; ++i) {
    check_sum += av[i][1];
  }

  {
    auto idx = 0;
    size_t sum = 0;
    for (auto num : section) {
      BOOST_CHECK(num == av[idx][1]);
      sum += num;
      idx++;
    }

    BOOST_CHECK(sum == check_sum);
  }
  {
    size_t idx = length - 1;
    size_t sum = 0;
    for (auto iter = section.rbegin(); iter != section.rend(); ++iter) {
      BOOST_CHECK(*iter == av[idx][1]);
      sum += *iter;
      idx--;
    }

    BOOST_CHECK(sum == check_sum);
  }
}

BOOST_AUTO_TEST_CASE(span_section_iteration) {
  int arr[4][2] = {{4, 0}, {5, 1}, {6, 2}, {7, 3}};

  // static bounds
  {
    span<int, 4, 2> av = arr;
    iterate_second_column(av);
  }
  // first bound is dynamic
  {
    span<int, dynamic_range, 2> av = arr;
    iterate_second_column(av);
  }
  // second bound is dynamic
  {
    span<int, 4, dynamic_range> av = arr;
    iterate_second_column(av);
  }
  // both bounds are dynamic
  {
    span<int, dynamic_range, dynamic_range> av = arr;
    iterate_second_column(av);
  }
}

BOOST_AUTO_TEST_CASE(dynamic_span_section_iteration) {
  auto height = 4, width = 2;
  auto size = height * width;

  auto arr = new int[size];
  for (auto i = 0; i < size; ++i) {
    arr[i] = i;
  }

  auto av = as_span(arr, size);

  // first bound is dynamic
  {
    span<int, dynamic_range, 2> av2 = as_span(av, dim<>(height), dim<>(width));
    iterate_second_column(av2);
  }
  // second bound is dynamic
  {
    span<int, 4, dynamic_range> av2 = as_span(av, dim<>(height), dim<>(width));
    iterate_second_column(av2);
  }
  // both bounds are dynamic
  {
    span<int, dynamic_range, dynamic_range> av2 =
        as_span(av, dim<>(height), dim<>(width));
    iterate_second_column(av2);
  }

  delete[] arr;
}

BOOST_AUTO_TEST_CASE(span_structure_size) {
  double(*arr)[3][4] = new double[100][3][4];
  span<double, dynamic_range, 3, 4> av1(arr, 10);

  struct EffectiveStructure {
    double *v1;
    ptrdiff_t v2;
  };
  BOOST_CHECK(sizeof(av1) == sizeof(EffectiveStructure));

  BOOST_CHECK_THROW(av1[10][3][4], fail_fast);

  span<const double, dynamic_range, 6, 4> av2 =
      as_span(av1, dim<>(5), dim<6>(), dim<4>());
  (void)av2;
}

BOOST_AUTO_TEST_CASE(fixed_size_conversions) {
  int arr[] = {1, 2, 3, 4};

  // converting to an span from an equal size array is ok
  span<int, 4> av4 = arr;
  BOOST_CHECK(av4.length() == 4);

  // converting to dynamic_range a_v is always ok
  {
    span<int, dynamic_range> av = av4;
    (void)av;
  }
  {
    span<int, dynamic_range> av = arr;
    (void)av;
  }

// initialization or assignment to static span that REDUCES size is NOT ok
#ifdef CONFIRM_COMPILATION_ERRORS
  { span<int, 2> av2 = arr; }
  { span<int, 2> av2 = av4; }
#endif

  {
    span<int, dynamic_range> av = arr;
    span<int, 2> av2 = av;
    (void)av2;
  }

#ifdef CONFIRM_COMPILATION_ERRORS
  {
    span<int, dynamic_range> av = arr;
    span<int, 2, 1> av2 = av.as_span(dim<2>(), dim<2>());
  }
#endif

  {
    span<int, dynamic_range> av = arr;
    span<int, 2, 1> av2 = as_span(av, dim<>(2), dim<>(2));
    auto workaround_macro = [&]() { return av2[{1, 0}] == 2; };
    BOOST_CHECK(workaround_macro());
  }

  // but doing so explicitly is ok

  // you can convert statically
  {
    span<int, 2> av2 = {arr, 2};
    (void)av2;
  }
  {
    span<int, 1> av2 = av4.first<1>();
    (void)av2;
  }

  // ...or dynamically
  {
    // NB: implicit conversion to span<int,2> from span<int,dynamic_range>
    span<int, 1> av2 = av4.first(1);
    (void)av2;
  }

  // initialization or assignment to static span that requires size INCREASE is
  // not ok.
  int arr2[2] = {1, 2};

#ifdef CONFIRM_COMPILATION_ERRORS
  { span<int, 4> av4 = arr2; }
  {
    span<int, 2> av2 = arr2;
    span<int, 4> av4 = av2;
  }
#endif
  {
    auto f = [&]() {
      span<int, 4> av9 = {arr2, 2};
      (void)av9;
    };
    BOOST_CHECK_THROW(f(), fail_fast);
  }

  // this should fail - we are trying to assign a small dynamic a_v to a
  // fixed_size larger one
  span<int, dynamic_range> av = arr2;
  auto f = [&]() {
    span<int, 4> av2 = av;
    (void)av2;
  };
  BOOST_CHECK_THROW(f(), fail_fast);
}

BOOST_AUTO_TEST_CASE(as_writeable_bytes) {
  int a[] = {1, 2, 3, 4};

  {
#ifdef CONFIRM_COMPILATION_ERRORS
    // you should not be able to get writeable bytes for const objects
    span<const int, dynamic_range> av = a;
    auto wav = av.as_writeable_bytes();
#endif
  }
//#ifdef TODO
  {
    span<int, dynamic_range> av;
    auto wav = as_writeable_bytes(av);
    BOOST_CHECK(wav.length() == av.length());
    BOOST_CHECK(wav.length() == 0);
    BOOST_CHECK(wav.size_bytes() == 0);
  }

  {
    span<int, dynamic_range> av = a;
    auto wav = as_writeable_bytes(av);
    BOOST_CHECK(wav.data() == (byte *)&a[0]);
    BOOST_CHECK(wav.length() == sizeof(a));
  }
//#endif  
}
//#ifdef TODO
BOOST_AUTO_TEST_CASE(iterator) {
  int a[] = {1, 2, 3, 4};

  {
    span<int, dynamic_range> av = a;
    auto wav = as_writeable_bytes(av);
    for (auto &b : wav) {
      b = byte(0);
    }
    for (size_t i = 0; i < 4; ++i) {
      BOOST_CHECK(a[i] == 0);
    }
  }

  {
    span<int, dynamic_range> av = a;
    for (auto &n : av) {
      n = 1;
    }
    for (size_t i = 0; i < 4; ++i) {
      BOOST_CHECK(a[i] == 1);
    }
  }
}
//#endif
BOOST_AUTO_TEST_SUITE_END()
}
}
