#include <stdio.h>

long foo(int *x, long *y) {
  *x = 0;
  *y = 1;
  return *x;
}

int main(void) {
  long l;
  printf("%ld\n", foo((int *)&l, &l));
}

/*

#include <stdio.h>

typedef struct { int i1; } s1;
typedef struct { int i2; } s2;

void f(s1 *s1p, s2 *s2p) {
  s1p->i1 = 2;
  s2p->i2 = 3;
  printf("%i\n", s1p->i1);
}

int main() {
  s1 s = {.i1 = 1};
  f(&s, (s2 *)&s);
}
*/
