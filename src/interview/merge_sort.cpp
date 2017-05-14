#include <vector>
#include <iostream>
#include <algorithm>
 
template<class Iter>
void merge_sort(Iter first, Iter last)
{
    if (last - first > 1) {
        Iter middle = first + (last - first) / 2;
        merge_sort(first, middle);
        merge_sort(middle, last);
        std::inplace_merge(first, middle, last);
    }
}
 
int main()
{
    std::vector<int> v{8, 2, -2, 0, 11, 11, 1, 7, 3};
    merge_sort(v.begin(), v.end());
    for(auto n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}


// https://codereview.stackexchange.com/questions/4582/sorting-algorithms-implemented-in-c
std::vector<int> merge(std::vector<int> &a, std::vector<int> &b) {
    std::vector<int> result;
    size_t i=0, j=0;
    while (i<a.size() && j<b.size())
        if (a[i] <= b[j])
            result.push_back(a[i++]);
        else
            result.push_back(b[j++]);
    // Copy tail. Only one of these loops will execute per invocation
    while (i<a.size())
        result.push_back(a[i++]);
    while (j<b.size())
        result.push_back(b[j++]);
    return result;
}

