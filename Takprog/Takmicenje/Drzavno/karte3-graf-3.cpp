#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int solve(const vector<int> &arr) {
  int n = arr.size();

  vector<int> sorted_arr = arr;
  sort(sorted_arr.begin(), sorted_arr.end());

  vector<bool> visited(n, false);
  int subsequences = 0;

  for (int i = 0; i < n; ++i) {
    if (visited[i] || arr[i] == sorted_arr[i])
      continue;

    ++subsequences;

    int j = i;
    while (!visited[j]) {
      visited[j] = true;
      j = find(sorted_arr.begin(), sorted_arr.end(), arr[j]) -
          sorted_arr.begin();
    }
  }

  return subsequences;
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
