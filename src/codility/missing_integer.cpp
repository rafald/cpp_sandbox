// https://app.codility.com/programmers/lessons/4-counting_elements/missing_integer/start/
//

#include <vector>
#include <algorithm> // partition iter_swap

int solution(std::vector<int> &A) {
   // reject nonpositive values
   auto const first_nonpositive = std::partition(A.begin(), A.end(), [](int i) {return i>0; });
   A.resize(std::distance(A.begin(), first_nonpositive));
   int const size = A.size();

   // it is enough to consider at most A.size() first positive integers /in worst case we have consecutive numbers/
   // scan them and mark as visisted by mutating to negative value,
   // if the value is outside the range then simply skip it /there must be empty slot in 1..N to compensate this/
   for(auto b = A.begin(); b!=A.end(); ++b)
   {
       // possible values start from 1, not 0 /range is shifted/
       // offset by -1 for all following calculations so mutation applies to the relevant index
       auto const idx = abs(*b)-1;
       if(idx < size) {
          A[idx] = - abs(A[idx]);
       }
   }
   // first positive value is related to the solution; take into account -1 offset
   for(int i = 0; i != size; i++)
      if (A[i] > 0)
        return i+1;

   return A.size()+1;
}

#include <unordered_set>
int standard_solution(std::vector<int> &A) {
    std::unordered_set<int> hs(A.begin(), A.end());
    int candidate =1;
    for(;;++candidate) { // this will finish before 1+A.size() iterations
        if(hs.count(candidate) == 0)
           break;
    }
    return candidate;
}

#include <iostream>
#include <fstream>
#include <iomanip>
/*
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <numeric>
*/
using namespace std;

int main(int argn, char const* argv[]) {
    cin.exceptions(ios_base::badbit | ios_base::failbit);
    cout.setf( ios::fixed, ios::floatfield );
    cout.precision(1);

    if (argn > 1) {
      static ifstream ifs{argv[1]};
      cin.rdbuf(ifs.rdbuf());
    }

    std::vector<int> samples;
    {
        int n = 0;
        cin >> n;
           samples.reserve(n);
        while(n-- > 0) {
            int i = 0;
            cin >> i;
            samples.push_back(i);
        }
    }

    auto result = solution(samples);
    cout << result << "\n";

    return 0;
}

/*
Write a function:

int solution(vector<int> &A);

that, given an array A of N integers, returns the smallest positive integer (greater than 0) that does not occur in A.

For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.

Given A = [1, 2, 3], the function should return 4.

Given A = [−1, −3], the function should return 1.

Assume that:

N is an integer within the range [1..100,000];
each element of array A is an integer within the range [−1,000,000..1,000,000].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).
Copyright 2009–2018 by Codility Limited. All Rights Reserved. Unauthorized copying, publication or disclosure prohibited.demo
*/
