// In C++1z mode, aggregate initialization can be performed for classes with
// base classes:

struct A {
  int n;
};
struct B : A {
  int x, y;
};
B b = {1, 2, 3}; // b.n == 1, b.x == 2, b.y == 3

int main() { return 0; }
