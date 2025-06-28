#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

bool cansum(int target, const vector<int>& choices){
  const int max = target + 1;
  vector<bool> table(max, false);
  int i;
  table[0] = true;
  for(i = 0; i < max; ++i)
    if(table[i])
      for(const auto& c : choices)
        if(i+c < max)
          table[i+c] = true; 
  return table[target];
}

//for how sum, just store a vector of jumps by which the index is reachable in that index
vector<int> bestsum(int target, vector<int> choices){
  sort(choices.begin(), choices.end());//, greater<int>());
  cout << "array:\n";
  for(auto& c : choices)
    cout << c << ' ';
  cout << '\n';

  const int max = target + 1;
  const int inf = 2100000000;
  vector<int> table(max, inf);
  int i;
  bool found = false;
  table[0] = 0;
  for(i = 0; i < max; ++i)
    if(table[i] != inf)
      for(const auto& c : choices){
        if(i+c < max)
          table[i+c] = min(i, table[i+c]);
        if(i+c == target){
          found = true;
          break;
        }
      }
  if(!found) return {};
  
  vector<int> solution;
  solution.emplace_back(target);
  while(target != 0){
    solution.emplace_back(table[target]);
    target = table[target];
  }
  reverse(solution.begin(), solution.end());
  return solution;
}

int main(){
  cout << (cansum(7, {2,3})?"true":"false") << '\n';
  cout << (cansum(7, {5,3,4})?"true":"false") << '\n';
  cout << (cansum(7, {2, 4})?"true":"false") << '\n';
  cout << (cansum(8, {2, 3, 5})?"true":"false") << '\n';
  cout << (cansum(300, {7, 14})?"true":"false") << '\n';

  vector<int> path = bestsum(8, {2, 3, 5});
  for(auto& u : path)
    cout << u << ' ';

  cout << '\n';

  path = bestsum(300, {7, 14});
  for(auto& u : path)
    cout << u << ' ';
  
  cout << '\n';

  path = bestsum(100, {1, 2, 5, 25});
  for (auto u : path)
    cout << u << ' ';

  cout << '\n';

  path = bestsum(8, {2,3,5});
  for (auto u : path)
    cout << u << ' ';
}

