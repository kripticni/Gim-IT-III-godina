#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>

[[gnu::hot]] [[gnu::always_inline]]
static inline bool poredi(const std::string& a, const std::string& b) {
  return a + b < b + a;
}

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::vector<std::string> arr;
  uint16_t n, i;

  std::cin >> n;
  arr = std::vector<std::string>(n);

  for(i = 0; i < n; ++i)
    std::cin >> arr[i];

  std::sort(arr.begin(), arr.end(), poredi);

  for(i = 0; i < n; ++i)
    std::cout << arr[i];
}
