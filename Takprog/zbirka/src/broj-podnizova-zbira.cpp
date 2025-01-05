#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>

constexpr float eps = 10e-5f;

[[gnu::hot]] [[gnu::flatten]]
static uint16_t brute(const float (&arr)[30], const register float &min,
                      const register float &max, float sum, uint16_t i,
                      const uint16_t &n) {
  [[assume(n < 30)]];
  if (i == n)
    return 0;

  uint16_t count = 0;
  register float cmp;
  for (; i < n; ++i) {
    cmp = arr[i] + sum;
    if (cmp < min) {
      count += brute(arr, min, max, sum + arr[i], i + 1, n);
      continue;
    }
    if (cmp > max)
      continue;

    ++count;
  }
  return count;
}

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  float input[30];
  float target;
  uint16_t n;

  std::cin >> n;
  for (uint16_t i = 0; i < n; ++i)
    std::cin >> input[i];
  std::cin >> target;

  std::cout << brute(input, target - eps, target + eps, 0, 0, n);
}
