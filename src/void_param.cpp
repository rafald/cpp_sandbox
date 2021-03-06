// https://github.com/insooth/VoidParam/blob/master/Solution.cpp

int
f(int i) {
   return i;
}

void
void_fun(void) {}
// void void_fun(void,void) {}
//*** invalid use of type ‘void’ in parameter declaration
// void void_fun(void const &) {}
//** error: cannot declare reference to ‘const void’
void
void_fun(void const*) {}

int
test() {
   f(4);
   f((void(), 4));
   // f( (void, 4) );
   f((void_fun(), 4));
   // just regular comma operator kicks off here !!!!!!
   // we can overload this comma operator
   // but it will be not defined for void type !!!!
   // there is no such thing like void input argument type
   // unless this is the only arg of function
   return 0;
}


//#include <exception>
#include <stdexcept>

template <typename T>
T
Process(const T& t) {
   return t;
}

struct VoidParam {};

inline void
Process(const VoidParam&) {
   throw std::logic_error("'void' parameter is not allowed");
}

// NOTE T == void instantiation is automatically removed
// but in case of in arg type like: const T* t  it is NOT REMOVED!!!
template <typename T>
T operator , (const T& t, const VoidParam&) {
   return t;
}

#define PROCESS(x) Process((x, VoidParam()))

void
GetVoid() {}

int
main() {
   PROCESS(1);

   PROCESS(GetVoid());

   PROCESS(void());
}
