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

#include <cassert>
#include <fstream>

using namespace std;

vector<int>
array_left_rotation(vector<int> a, int n, int k) {
   k %= n;
   auto first = a.begin();
   assert(first + n <= a.end());
   rotate(first, first + k, first + n);
   a.resize(n);
   return a;
}

int
main(int argn, char const* argv[]) {
   if (argn > 1) {
      static ifstream ifs{argv[1]};
      cin.rdbuf(ifs.rdbuf());
   }

   int n;
   int k;
   cin >> n >> k;
   vector<int> a(n);
   for (int a_i = 0; a_i < n; a_i++) { cin >> a[a_i]; }
   vector<int> output = array_left_rotation(a, n, k);
   for (int i = 0; i < n; i++) cout << output[i] << " ";
   cout << endl;
   return 0;
}
