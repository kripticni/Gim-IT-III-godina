#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

uint32_t solve(const vector<int64_t> &takmicari);
vector<pair<uint32_t, uint32_t>> find_zerosum_arrs(const vector<int64_t> &arr);
vector<pair<uint32_t, uint32_t>>
merge_intervals(const vector<pair<uint32_t, uint32_t>> &intervals);

uint32_t solve(const vector<int64_t> &takmicari) {
  vector<pair<uint32_t, uint32_t>> zerosum_arrs = find_zerosum_arrs(takmicari);

  // for (auto p : zerosum_arrs)
  //   cout << p.first << ':' << p.second << '\n';

  sort(zerosum_arrs.begin(), zerosum_arrs.end());
  zerosum_arrs = merge_intervals(zerosum_arrs);
  // cout << "\n\n  merged:\n";

  // for (auto p : zerosum_arrs)
  //   cout << p.first << ':' << p.second << '\n';

  unordered_map<int64_t, uint32_t> freq_map;
  uint32_t max_freq = 0;
  uint32_t j;
  for (const auto &p : zerosum_arrs) {
    for (j = p.first; j <= p.second; ++j) {
      freq_map[takmicari[j]]++;
      max_freq = max(max_freq, freq_map[takmicari[j]]);
      // cout << "on: " << takmicari[j] << ':' << freq_map[takmicari[j]] <<
      // '\n';
    }
    freq_map.clear();
  }

  return max_freq;
}

vector<pair<uint32_t, uint32_t>> find_zerosum_arrs(const vector<int64_t> &arr) {
  unordered_map<int64_t, vector<int64_t>> prefix_map;
  vector<pair<uint32_t, uint32_t>> ret;

  int64_t prefix_sum = 0;
  for (uint32_t i = 0; i < arr.size(); ++i) {
    prefix_sum += arr[i];

    if (prefix_sum == 0)
      ret.emplace_back(0, i);

    if (prefix_map.find(prefix_sum) != prefix_map.end()) {
      for (int64_t start_idx : prefix_map[prefix_sum])
        ret.emplace_back(start_idx + 1, i);
    }

    prefix_map[prefix_sum].emplace_back(i);
  }

  return ret;
}

vector<pair<uint32_t, uint32_t>>
merge_intervals(const vector<pair<uint32_t, uint32_t>> &intervals) {

  vector<pair<uint32_t, uint32_t>> merged;
  uint32_t i;

  merged.push_back(intervals[0]);
  for (i = 1; i < intervals.size(); ++i) {
    auto &last = merged.back();
    auto &curr = intervals[i];

    if (curr.first == last.first)
      last.second = max(last.second, curr.second);
    else if (curr.second == last.second)
      last.first = min(last.first, curr.first);
    else if (curr.first == last.second + 1)
      last.second = curr.second;
    else if (curr.first > last.first && curr.first < last.second &&
             curr.second < last.second && curr.second > last.first) {
      // cout << '{' << last.first << ',' << last.second << "}: skipped "
      //      << curr.first << ',' << curr.second;
      continue;
    } else
      merged.push_back(curr);
  }

  return merged;
}

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  vector<int64_t> takmicari;
  uint32_t n;
  uint32_t i;

  cin >> n;
  takmicari = vector<int64_t>(n);
  for (i = 0; i < n; ++i)
    cin >> takmicari[i];
  cout << solve(takmicari);
}
