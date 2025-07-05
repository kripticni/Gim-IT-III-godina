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

int64_t solve(const vector<int64_t> &arr);
int64_t ldslen(const vector<int64_t> &arr);

[[gnu::hot]]
int64_t solve(const vector<int64_t> &arr) {
  vector<int64_t> reversed(arr.rbegin(), arr.rend());
  return ldslen(reversed);
}

int64_t ldslen(const vector<int64_t> &arr) {
  vector<int64_t> lds;
  for (int64_t k : arr) {
    auto it = lower_bound(lds.begin(), lds.end(), k);
    if (it == lds.end())
      lds.emplace_back(k);
    else
      *it = k;
  }
  return lds.size();
}

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  vector<int64_t> karte;
  int64_t n, q;
  int64_t i, j;

  cin >> n >> q;
  karte = vector<int64_t>(n);
  for (i = 0; i < n; ++i)
    cin >> karte[i];

  /*
  cout << '{';
  for (auto k : karte)
    cout << k << ' ';
  cout << "}: ";
  */
  cout << solve(karte) - 1 << '\n';
  for (j = 0; j < q; ++j) {
    int64_t qi, qj;
    cin >> qi >> qj;
    swap(karte[qi - 1], karte[qj - 1]);

    /*
    cout << '{';
    for (auto k : karte)
      cout << k << ' ';
    cout << "}: ";
    */

    cout << solve(karte) - 1 << '\n';
  }
}
