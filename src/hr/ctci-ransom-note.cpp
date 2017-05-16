// clang++-4.0 -std=c++1z

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

bool
ransom_note(vector<string> magazine, vector<string> ransom) {
   std::sort(magazine.begin(), magazine.end());
   std::sort(ransom.begin(), ransom.end());
   return includes(magazine.begin(), magazine.end(), ransom.begin(), ransom.end());
}

int
main(int argn, char const* argv[]) {
   if (argn > 1) {
      static ifstream ifs{argv[1]};
      cin.rdbuf(ifs.rdbuf());
   }
   int m;
   int n;
   cin >> m >> n;
   vector<string> magazine(m);
   for (int magazine_i = 0; magazine_i < m; magazine_i++) { cin >> magazine[magazine_i]; }
   vector<string> ransom(n);
   for (int ransom_i = 0; ransom_i < n; ransom_i++) { cin >> ransom[ransom_i]; }
   if (ransom_note(magazine, ransom))
      cout << "Yes\n";
   else
      cout << "No\n";
   return 0;
}

