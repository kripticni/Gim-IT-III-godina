#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>

[[gnu::always_inline]]
static inline void print(const uint8_t (&tabla)[8][8], const uint8_t &m,
                         const uint8_t &n) {
  for (uint8_t i = 0; i < m; ++i) {
    for (uint8_t j = 0; j < n; ++j)
      std::cout << std::setw(2) << (uint16_t)tabla[i][j] << ' ';
    std::cout << '\n';
  }
  std::cout << '\n';
}

int8_t max;
static const int8_t x[8] = {2, 2, -2, -2, 1, 1, -1, -1};
static const int8_t y[8] = {1, -1, 1, -1, 2, -2, 2, -2};

[[gnu::hot]] [[gnu::always_inline]]
static inline bool isSafe(const uint8_t (&tabla)[8][8], const int8_t &i,
                          const int8_t &j, const uint8_t &m, const uint8_t &n) {
  if (i < m && i >= 0 && j < n && j >= 0 && tabla[i][j] == 0)
    return true;
  return false;
}

[[gnu::hot]]
static void solve(uint8_t (&tabla)[8][8], int8_t i, int8_t j, uint8_t counter,
                  const int8_t &m, const int8_t &n, const int8_t &max) {
  if (counter == max) {
    print(tabla, m, n);
    return;
  }

  for (int8_t k = 0; k < 8; ++k)
    if (isSafe(tabla, i + x[k], j + y[k], m, n)) {
      tabla[i + x[k]][j + y[k]] = counter;
      solve(tabla, i + x[k], j + y[k], counter + 1, m, n, max);
      tabla[i + x[k]][j + y[k]] = 0;
    }
}

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  uint8_t tabla[8][8] = {};
  int8_t m;
  int8_t n;
  tabla[0][0] = 1;

  {
    int16_t input;
    std::cin >> input;
    m = input;
    std::cin >> input;
    n = input;
  }
  max = m * n + 1;

  solve(tabla, 0, 0, 2, m, n, max);
}
