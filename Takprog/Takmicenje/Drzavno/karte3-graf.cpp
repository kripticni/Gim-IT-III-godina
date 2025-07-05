#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

typedef unordered_map<uint16_t, unordered_map<uint16_t, int16_t>> Graph;
constexpr int16_t INF = 30000;
constexpr int16_t NEG_INF = -30000;
constexpr int16_t unvisited = -1;

uint32_t solve(const vector<uint32_t> &arr);

[[gnu::hot]]
uint32_t solve(const vector<uint32_t> &arr) {
  vector<uint32_t> dp(arr.size(), 1);
  uint32_t n = arr.size();

  for (uint32_t i = 1; i < n; ++i)
    for (uint32_t j = 0; j < i; ++j)
      if (arr[i] > arr[j])
        dp[i] += dp[j];

  uint32_t sequences = 0;
  for (uint32_t i = 0; i < n; ++i)
    sequences += dp[i];

  return sequences;
}

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  vector<uint32_t> karte;
  uint32_t n, q;
  uint32_t i, j;

  cin >> n >> q;
  karte = vector<uint32_t>(n);
  for (i = 0; i < n; ++i)
    cin >> karte[i];

  /*
  cout << '{';
  for (auto k : karte)
    cout << k << ' ';
  cout << "}: ";
  */
  cout << solve(karte) << '\n';
  for (j = 0; j < q; ++j) {
    uint32_t qi, qj;
    cin >> qi >> qj;
    swap(karte[qi - 1], karte[qj - 1]);

    /*
    cout << '{';
    for (auto k : karte)
      cout << k << ' ';
    cout << "}: ";
    */

    cout << solve(karte) << '\n';
  }
}
