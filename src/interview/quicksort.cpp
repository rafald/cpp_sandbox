#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <forward_list>

using namespace std;

template <class ForwardIt>
 void quicksort(ForwardIt first, ForwardIt last)
 {
    if(first == last) return;
    auto const pivot = *std::next(first, std::distance(first,last)/2);
    auto m1 = partition(first, last, [pivot](const auto & el){return el<pivot; });
    auto m2 = partition(m1, last, [pivot](const auto & el){return !(el<pivot); });
    quicksort(first, m1);
    quicksort(m2, last);
 }

int main()
{
    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9};
    std::cout << "Original vector:\n    ";
    for (int elem : v) std::cout << elem << ' ';
 
    auto it = std::partition(v.begin(), v.end(), [](int i){return i % 2 == 0;});
 
    std::cout << "\nPartitioned vector:\n    ";
    std::copy(std::begin(v), it, std::ostream_iterator<int>(std::cout, " "));
    std::cout << " * ";
    std::copy(it, std::end(v), std::ostream_iterator<int>(std::cout, " "));
 
    std::forward_list<int> fl = {1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92};
    std::cout << "\nUnsorted list:\n    ";
    for(int n : fl) std::cout << n << ' ';
    std::cout << '\n';  
 
    quicksort(std::begin(fl), std::end(fl));
    std::cout << "Sorted using quicksort:\n    ";
    for(int fi : fl) std::cout << fi << ' ';
    std::cout << '\n';

    auto const expected = R"YXC(Original vector:
    0 1 2 3 4 5 6 7 8 9 
Partitioned vector:
    0 8 2 6 4  *  5 3 7 1 9 
Unsorted list:
    1 30 -4 3 5 -4 1 6 -8 2 -5 64 1 92 
Sorted using quicksort:
    -8 -5 -4 -4 1 1 1 2 3 5 6 30 64 92)YXC";
    std::cout << expected;
}

