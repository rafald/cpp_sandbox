// https://stackoverflow.com/questions/7159342/given-an-array-of-integers-find-the-largest-subarray-with-the-maximum-sum#7159452
// https://en.wikipedia.org/wiki/Maximum_subarray_problem

#include <climits>
#include <tuple>

/*
sum[0] = max(0, A[0])
sum[j] = max(0, sum[j-1] + A[j])

?
sum[0] = A[0]
sum[j] = max(A[j], sum[j-1] + A[j])

def max_subarray(A):
     max_ending_here = max_so_far = A[0]
     for x in A[1:]:
         max_ending_here = max(x, max_ending_here + x)
         max_so_far = max(max_so_far, max_ending_here)
     return max_so_far
 */
template <class It>
auto get_max_sum(It b, It const e) -> std::tuple<int,It,It>
{
   if(b==e) return {0,b,e};

    int best_sum = INT_MIN, candidate_sum = 0;
    auto candidate_start = b;

    It best_start = b;
    It best_end = b;
    for(; b != e; ++b)
    {
        candidate_sum += *b;
        if(candidate_sum > best_sum or
        // if the sum is equal, choose the one with more elements
        (candidate_sum == best_sum and std::distance(best_start,best_end) < std::distance(candidate_start, b+1)))
        {
            best_sum = candidate_sum;
            best_start = candidate_start;
            best_end = b + 1;
        }
        if(candidate_sum < 0)//????
        {
            candidate_sum = 0;
            candidate_start = b + 1;
        }
    }

    return std::tuple{best_sum,best_start,best_end};
    //return {best_sum,best_start,best_end};
}

template <class It>
auto get_max_sum2(It b, It const e) -> int
{
   auto max_ending_here = *b;
   auto max_so_far = max_ending_here;
   for(++b;b!=e;++b) {
      max_ending_here = max(*b, max_ending_here + *b);
      max_so_far = max(max_so_far, max_ending_here);
   }
   return max_so_far;
}

// D & C
// Sequential and Parallel Algorithms for the
// Generalized Maximum Subarray Problem
// https://pdfs.semanticscholar.org/bea4/1795adaf240b9db4195b9dc511bd8d46bff1.pdf
/*
   procedure MaxSum(f,t) begin
   //Finds maximum sum in a[f..t]
      if f = t then return (a[f], sum[f − 1], sum[f]) //One-element array
      c ← (f + t − 1)/2 //Halves array. left is a[f..c], right is a[c+1..t]
      (mLeft, minPLeft, maxPLeft) ← MaxSum(f,c)
      (mRight, minPRight, maxPRight) ← MaxSum(c + 1,t)
      minP ← MIN {minPLeft, minPRight} //Min prefix sum in sum[f−1..t−1]
      maxP ← MAX {maxPLeft, maxPRight} //Max prefix sum in sum[f..t]
      mCenter ← maxPRight − minPLeft //Solution for the center problem
      M ← MAX {mLeft, mRight, mCenter}
      return (M, minP, maxP)
   end

T(n)= 2T(n/2) + O(1), T(1) = O(1)
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using std::ios_base;
using std::ios;
using std::cin;
using std::cout;

int main(int argn, char const* argv[]) {
    cin.exceptions(ios_base::badbit | ios_base::failbit);
    cout.setf( ios::fixed, ios::floatfield );
    cout.precision(1);

    if (argn > 1) {
      static std::ifstream ifs{argv[1]};
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

    auto result = get_max_sum(samples.begin(), samples.end());
    cout << std::get<0>(result) << "\t";
    for(auto f = std::get<1>(result); f != std::get<2>(result); ++f)
         cout << *f << "+";
    cout << "\n";

    return 0;
}

/*
Given an array of integers. Find the LARGEST subarray with the MAXIMUM sum
*/
