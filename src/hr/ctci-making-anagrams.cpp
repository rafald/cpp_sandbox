// clang++-4.0 -std=c++11

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int number_needed(string a, string b) {
    using map_t = unordered_map<char,int>;
    map_t hist;
    for_each(a.begin(),a.end(),[&hist](char c){ ++hist[c]; });
    // 'subtract' b histogram
    for_each(b.begin(),b.end(),[&hist](char c){ --hist[c]; });
    
    return accumulate(hist.begin(), hist.end(), 0, [](int acc, map_t::value_type v){ return acc + abs(v.second); } );
}

int main(int argn, char const * argv[]){
    if(argn>1) {
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
