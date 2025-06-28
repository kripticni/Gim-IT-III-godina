#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

vector<uint32_t> best_sum(uint32_t target, vector<uint32_t> choices);
bool dfs(uint32_t target, const vector<uint32_t> &choices,
         vector<uint32_t> &solution);
bool dfs_memo(uint32_t target, const vector<uint32_t> &choices,
         vector<uint32_t> &solution);

vector<uint32_t> best_sum(uint32_t target, vector<uint32_t> choices) {
  // first, we sort the array to always take the largest numbers
  // so that we always have the shortest path, so we can return early
  sort(choices.begin(), choices.end(), greater<uint32_t>());
  vector<uint32_t> solution;
  dfs_memo(target, choices, solution);
  return solution;
}

bool dfs(uint32_t target, const vector<uint32_t> &choices,
         vector<uint32_t> &solution) {
  if (target == 0)
    return true;
  if (target < 0 || target > 4294967249)
    return false;

  for (uint32_t choice : choices)
    if (dfs(target - choice, choices, solution)) {
      solution.emplace_back(choice);
      return true;
    } else continue;
  return false;
}

#include <unordered_map>
unordered_map<uint32_t, bool> memo;
bool dfs_memo(uint32_t target, const vector<uint32_t> &choices,
         vector<uint32_t> &solution) {
  if (target == 0)
    return true;
  if(memo.count(target)) return memo[target];

  for (uint32_t choice : choices)
    if(choice > target) continue;
    else if (dfs_memo(target - choice, choices, solution)) {
      solution.emplace_back(choice);
      return true;
    } 

  memo[target] = false;
  return false;
}

int main() noexcept {
  auto combination = best_sum(100, {1, 2, 5, 25});
  for (auto c : combination)
    cout << c << '\n';
  auto solution2 = best_sum(8, {2,3,5});
  for (auto c : solution2)
    cout << c << '\n';
}
