// https://stackoverflow.com/questions/7159342/given-an-array-of-integers-find-the-largest-subarray-with-the-maximum-sum#7159452

#include <climits>
#include <tuple>

template <class It>
auto get_max_sum(It b, It const e) -> std::tuple<int,It,It>
{
   if(b==e) return {0,b,e};

   auto array = b;
   //auto len = std::distance(b,e);

    int max_sum = INT_MIN, candidate_sum = 0;
    auto candidate_start = b;

    It start = b;
    It end = b;
    //for(int i = 0; i != len; ++i)
    for(; b != e; ++b)
    {
        candidate_sum += *b;
        // if the sum is equal, choose the one with more elements
        if(candidate_sum > max_sum or (candidate_sum == max_sum and std::distance(start,end) < std::distance(candidate_start, b+1)))
        {
            max_sum = candidate_sum;
            start = candidate_start;
            end = b + 1;
        }
        if(candidate_sum < 0)
        {
            candidate_sum = 0;
            candidate_start = b + 1;
        }
    }

    return {max_sum,start,end};
}


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
