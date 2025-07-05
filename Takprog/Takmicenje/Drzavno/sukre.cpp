#include <algorithm>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iostream>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef unordered_map<uint16_t, unordered_map<uint16_t, int16_t>> Graph;
constexpr int16_t INF = 30000;
constexpr int16_t NEG_INF = -30000;
constexpr int16_t unvisited = -1;

[[gnu::always_inline]]
static inline unordered_set<string> generate(const string &arr) {
  uint32_t n = arr.size();
  unordered_set<string> results;

  for (uint32_t l = 0; l < n; ++l) {
    uint32_t xor_range = 0;

    for (uint32_t r = l; r < n; ++r) {
      xor_range ^= (arr[r] - '0');

      string subarr = arr.substr(0, l);
      subarr += (xor_range == 0) ? '0' : '1';
      subarr += arr.substr(r + 1);

      results.insert(subarr);
    }
  }
  return results;
}

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  string input;
  cin >> input;

  auto results = generate(input);
  // for (auto s : combinations)
  //   cout << s << '\n';
  cout << results.size();
}
