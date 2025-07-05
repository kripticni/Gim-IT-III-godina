#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int lis_length(const vector<int> &arr) {
  vector<int> lis;
  for (int num : arr) {
    auto it = lower_bound(lis.begin(), lis.end(), num);
    if (it == lis.end()) {
      lis.push_back(num);
    } else {
      *it = num;
    }
  }
  return lis.size();
}

int solve(const vector<int> &arr) {
  if (is_sorted(arr.begin(), arr.end()))
    return 1;
  int n = arr.size();
  int lis_len = lis_length(arr);
  return n - lis_len;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> karte(n);
  for (int i = 0; i < n; ++i) {
    cin >> karte[i];
  }

  cout << solve(karte) << '\n';

  for (int j = 0; j < q; ++j) {
    int qi, qj;
    cin >> qi >> qj;
    swap(karte[qi - 1], karte[qj - 1]);
    cout << solve(karte) << '\n';
  }

  return 0;
}
