#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

bool memoization(string pattern, vector<string>& choices);
inline bool startswith(const string& str, const string& prefix);

bool canConstruct(string pattern, vector<string> choices){
  return memoization(pattern, choices);
}


unordered_map<string, bool> memo;
bool memoization(string pattern, vector<string>& choices){
  if(pattern.empty()) return true;
  if(memo.count(pattern)) return memo[pattern];

  for(auto& c : choices)
  if(startswith(pattern, c))
    if(memoization(pattern.substr(c.length()), choices)){
      memo[pattern] = true;
      return true;
    }
     

  memo[pattern] = false;
  return false;
}

inline bool startswith(const string& str, const string& prefix) {
    return str.size() >= prefix.size() &&
           str.compare(0, prefix.size(), prefix) == 0;
}

int main() noexcept {
  auto solution = canConstruct("skateboard", {"bo","rd","ate","t","ska","sk","boar"});
  cout << ((solution)?"true\n":"false\n");
  solution = canConstruct("abcdef", {"ab","abc","cd","def","abcd"});
  cout << ((solution)?"true\n":"false\n");
}
