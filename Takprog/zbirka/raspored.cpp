#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::vector<std::pair<uint32_t, uint32_t>> arr;
  uint32_t n;
  std::cin >> n;

  arr.reserve(n);

  for (uint32_t i = 0; i < n; ++i) {
    uint16_t h, m;
    uint32_t start, end;

    std::cin >> h >> m;
    start = h * 60 + m;

    std::cin >> h >> m;
    end = h * 60 + m;

    arr.emplace_back(start, end);
  }

  std::sort(arr.begin(), arr.end(), [](const std::pair<uint32_t, uint32_t>& a, 
                                       std::pair<uint32_t, uint32_t>& b){
            return a.second < b.second;
            }
            );

  uint32_t br = 0, end = 0;
  for(uint32_t i = 0; i < n; ++i)
    if(arr[i].first >= end){
      end = arr[i].second;
      ++br;
    }

  std::cout << br;
}
