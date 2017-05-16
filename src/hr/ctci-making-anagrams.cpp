// clang++-4.0 -std=c++11

#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int
number_needed(string a, string b) {
   using map_t = unordered_map<char, int>;
   map_t hist;
   for_each(a.begin(), a.end(), [&hist](char c) { ++hist[c]; });
   // 'subtract' b histogram
   for_each(b.begin(), b.end(), [&hist](char c) { --hist[c]; });

   return accumulate(hist.begin(), hist.end(), 0, [](int acc, map_t::value_type v) { return acc + abs(v.second); });
}

int
main(int argn, char const* argv[]) {
   if (argn > 1) {
      static ifstream ifs{argv[1]};
      cin.rdbuf(ifs.rdbuf());
   }
   string a;
   cin >> a;
   string b;
   cin >> b;
   cout << number_needed(a, b) << endl;
   return 0;
}

/*
from collections import Counter

def number_needed(a, b):
    freq_a, freq_b = Counter(a), Counter(b)
    freq_a.subtract(freq_b)
    return sum([abs(x) for x in freq_a.values()])
*/
