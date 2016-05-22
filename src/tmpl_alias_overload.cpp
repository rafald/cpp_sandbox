#include <iostream>
#include <string>

using namespace std;

template <class T, template <typename> class Forward> struct X {
  Forward<T> t;
  using type = T;
  X() { std::cout << "1"; }
};

/*
template <typename T>
struct Y { using type = T; };*/
template <typename T> using Y = T;

template <typename T> using Z = Y<T>;

template <typename T> using W = Z<T>;

/*
template <class T>
struct X<T,Y> {
  X() { std::cout << "2"; }
  // must be repeated in specialisation
  T t;
  using type = T;
};
*/
template <class T> void f(X<T, Z> const &xz) { cout << "{X<Z>}" << xz.t; }
template <class T> void f(X<T, Y> const &xy) { cout << "{X<Y>}" << xy.t; }
template <class T> void f(X<T, W> const &xw) { cout << "{X<W>}" << xw.t; }

/*
//       template <typename T> using Z = Y<T>; //Z is NOT JUST AN ALIAS for Y,
but Z<T> is some alias for Y<T>
// altough Z and Y are different type families (again Z is not just an alias for
Y), both Z<T> and Y<T> reduce to the same type
// so following does not compile
template <class T>
void
g(Z<T>)
{
    cout << "{g(z)}";
}
template <class T>
void
g(Y<T>)
{
    cout << "{g(y)}";
}
*/

int main() {
  X<int, Y> xy;
  xy.t = 3;
  X<int, Z> xz;
  xz.t = 5;
  X<int, W> xw;
  xw.t = 7;
  f(xy);
  f(xz);
  f(xw);

  /*
  Y<int> yi;
  Z<int> zi;
  g(yi);
  g(zi);  */
}
