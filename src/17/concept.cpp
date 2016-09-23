// No main here! #define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#ifndef __cpp_concepts
static_assert(false, "Concepts TS found not found");
#endif
// __cpp_concepts >= 201507
 
template <typename T>
concept bool Identity = true;
////////////////////////////////////////
template <typename T>
concept bool Surface() {
    return requires(T& t, std::pair<float,float> p, float radius) {
        { t.move_to(p) };
        { t.line_to(p) };
        { t.arc(p, radius) };
        // etc...
    };
}
/* 
template <typename S>
    requires Surface<S>()
void draw(S& surface) const;

struct triangle {
    void draw(Surface& surface) const;
};

static_assert(Drawable<triangle>(), ""); // Should pass
*/
////////////////////////////////////////
template <class T>
concept bool EqualityComparable() { 
    return requires(T a, T b) {
        {a == b} -> bool;//Boolean; // Boolean is the concept defining a type usable in boolean context
        {a != b} -> bool;//Boolean;
    };
}
////////////////////////////////////////
template <class C>
concept bool Sortable() { 
    return requires(C c) {
        {c[0] < c[0]} -> bool;//Boolean;
    };
}
  
////////////////////////////////////////
////////////////////////////////////////
std::vector<int>
f(int i) {
  return {1,2,i};
}

BOOST_AUTO_TEST_CASE(test_concept) {
  int y = 7;
  BOOST_CHECK_EQUAL(y, 7);

  auto x1 = f(y); // the type of x1 is deduced to whatever f returns
  Sortable x2 = f(y); // the type of x2 is deduced, but only compiles if it satisfies Sortable
}

