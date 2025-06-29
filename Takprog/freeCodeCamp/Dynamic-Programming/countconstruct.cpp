#include <iostream>
#include <vector>
#include <string>
using namespace std;

int countConstruct(string pattern, vector<string> choices);
inline bool startswith(const string& str, const string& prefix);

int countConstruct(string pattern, vector<string> choices){
  const int max = pattern.length() + 1;
  vector<int> table(max, 0);
  table[0] = 1;

  int i;
  for(i = 0; i < max; ++i)
    if(table[i] > 0)
      for(const auto& c : choices)
        if(startswith(pattern.substr(i), c))
          if(i + c.length() < max)
            table[i + c.length()] += table[i];
  return table[max-1];
}

inline bool startswith(const string& str, const string& prefix) {
  return str.size() >= prefix.size() &&
  str.compare(0, prefix.size(), prefix) == 0;
}

int main(){
  cout << countConstruct("purple", {"purp","p","ur","le","purpl"});
}
