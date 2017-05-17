// clang++-4.0 -std=c++14

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
is_scope_exit(char scope_enter, char scope_exit) {
   unordered_map<char, char> const static enter_exit = {
       {'{', '}'}, {'(', ')'}, {'[', ']'},
   };
   auto const found = enter_exit.find(scope_enter);
   return enter_exit.end() != found && scope_exit == found->second;
};

bool
is_balanced(string expression) {
   if (expression.empty()) return true;

   std::stack<char> scopes_interpreter;
   for_each(expression.begin(), expression.end(), [&scopes_interpreter](char next) {
      if (scopes_interpreter.empty())
         scopes_interpreter.push(next);
      else {
         if (is_scope_exit(scopes_interpreter.top(), next))
            scopes_interpreter.pop();
         else
            scopes_interpreter.push(next);
      }
   });
   return scopes_interpreter.empty();
}

int
main() {
   int t;
   cin >> t;
   for (int a0 = 0; a0 < t; a0++) {
      string expression;
      cin >> expression;
      bool answer = is_balanced(expression);
      if (answer)
         cout << "YES\n";
      else
         cout << "NO\n";
   }
   return 0;
}

/* TODO grammar
expr = s1 | s2 |s3
s1 = { expr }
s2 = [ expr ]
s3 = ( expr )
*/

/*
bool is_balanced(string expression) {
  stack<char> s;
  for (char c : expression) {
    if      (c == '{') s.push('}');
    else if (c == '[') s.push(']');
    else if (c == '(') s.push(')');
    else {
      if (s.empty() || c != s.top())
        return false;
      s.pop();
    }
  }
  return s.empty();
}
*/

