#include <iostream>
#include <utility>
#include <limits>
#include <cstdint>

#include <boost/format.hpp>

//#include "ftrapv.cpp"

//using namespace std;

extern "C" int subtract_overflow; //TODO header with destrctive read functions readr_add_overflows() read-reset
extern "C" int int_add_overflow;
extern "C" int long_add_overflow;
#if defined(_MSC_VER)
// dummy flags
int subtract_overflow;
int int_add_overflow;
int long_add_overflow;
#endif

int
main() {
   try {
   std::cout << std::numeric_limits<long long>::max() << "\t" << std::numeric_limits<intmax_t>::max() /*<< "\t" << LLONG_MAX*/ << "\n";
   std::cout << std::numeric_limits<unsigned long long>::max() << "\t" << std::numeric_limits<uintmax_t>::max() /*<< "\t" << ULLONG_MAX*/ << "\n";
   
  auto next_fib = [i = 0LL, j = 1LL]() mutable {
     i = std::exchange(j, i + j);
     if(long_add_overflow) {
        //std::cout << " 0LL add_overflow ";
        i = 0LL; j = 1LL;
        long_add_overflow = 0;
     }
     return i;
  }; 
  auto unext_fib = [i = 0ULL, j = 1ULL]() mutable {
     i = std::exchange(j, i + j);
     if(long_add_overflow) {
        std::cout << " 0ULL add_overflow ";
        i = 0ULL; j = 1ULL;
        long_add_overflow = 0;
     }
     return i;
  }; 
  
  auto next_fib3 = [i = 0LL, j = 1LL, k = 1LL]() mutable {
     i = std::exchange(j, i + j);
     j = std::exchange(k, j + k);
     if(long_add_overflow) {
        std::cout << " 0LL add_overflow ";
        i = 0LL; j = k = 1LL;
        long_add_overflow = 0;
     }
     return j;
  }; 
  auto unext_fib3 = [i = 0ULL, j = 1ULL, k = 1ULL]() mutable {
     i = std::exchange(j, i + j);
     j = std::exchange(k, j + k);
     if(long_add_overflow) {
        std::cout << " 0ULL add_overflow ";
        i = 0ULL; j = k = 1ULL;
        long_add_overflow = 0;
     }
     return j;
  }; 
  
  for(int i = 0; i!=99 ; ++i) {
     auto const fib = next_fib();
     auto const fib3 = next_fib3();
     std::cout << boost::format("%3s %25s %25s %25s %25s %8s\n") 
         % i % fib % unext_fib() % fib3 % unext_fib3() % (fib? (fib3/fib): 0);
  }
  
  //std::cout << "add_overflow: " << add_overflow << "\n";
  //std::cout << "subtract_overflow: " << subtract_overflow << "\n";
   } catch( std::exception const & ex )
   {
      //std::cout << ex.what();
      std::exit(0);
   }
}
