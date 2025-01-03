#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>

[[gnu::always_inline]]
static inline void print(const uint8_t (&solution)[6][6], const uint8_t &n) {
  for (uint8_t i = 0; i < n; ++i) {
    for (uint8_t j = 0; j < n; ++j)
      std::cout << (uint16_t)solution[i][j];
    std::cout << '\n';
  }
  std::cout << '\n';
}

[[gnu::hot]] [[gnu::flatten]]
static void solve(uint8_t (&solution)[6][6], uint8_t (&row)[6],
                  uint8_t (&col)[6], uint8_t i, uint8_t j, const uint8_t n,
                  const uint8_t vmax) noexcept {
  if (i >= n) {
    i = 0;
    ++j;
    if (j >= n) {
      print(solution, n);
      return;
    }
  }

  if (solution[i][j]) {
    solve(solution, row, col, i + 1, j, n, vmax);
    return;
  }

  uint8_t possible = row[i] | col[j];
  if (possible == vmax)
    return;

  for (uint8_t k = 0; k < n; ++k) {
    if (possible & (1 << k))
      continue;

    row[i] |= 1 << k;
    col[j] |= 1 << k;
    solution[i][j] = k + 1;

    solve(solution, row, col, i + 1, j, n, vmax);

    row[i] &= ~(1 << k);
    col[j] &= ~(1 << k);
    solution[i][j] = 0;
  }
}

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  alignas(64) uint8_t kvadrat[6][6] = {{0, 0}};
  uint8_t row[6] = {0};
  uint8_t col[6] = {0};
  uint8_t max = 0;
  uint8_t n;

  std::cin >> n;
  n -= 48; // konverzija iz uchar u uint

  for (uint8_t i = 0; i < n; ++i) {
    max |= 1 << i;
    for (uint8_t j = 0; j < n; ++j) {
      char input;
      std::cin >> input;
      input -= 48;
      if (input > 0) {
        kvadrat[i][j] = input;
        --input; // zero indexing
        row[i] |= 1 << input;
        col[j] |= 1 << input;
      }
    }
  }

  solve(kvadrat, row, col, 0, 0, n, max);
}
