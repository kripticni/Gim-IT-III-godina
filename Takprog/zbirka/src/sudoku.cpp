#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

static inline void print(uint8_t (&sudoku)[9][9]) {
  uint8_t i, j;
  for (i = 0; i < 9; ++i) {
    for (j = 0; j < 9; ++j)
      std::cout << (uint16_t)sudoku[i][j];
    std::cout << '\n';
  }
  exit(0);
}

// considering one solution must exist
[[gnu::hot]]
static void solve(uint8_t (&map)[9][9], uint16_t (&row)[9], uint16_t (&col)[9],
                  uint16_t (&sqr)[9], uint8_t i, uint8_t j) noexcept {
  if (i > 8) {
    ++j;
    i = 0;
    if (j > 8) {
      print(map);
      return;
    }
  }

  if (map[i][j]) {
    solve(map, row, col, sqr, i + 1, j);
    return;
  }

  uint16_t possible;
  possible = row[i] | col[j] | sqr[(i / 3) * 3 + j / 3];
  if (possible == 511) { // svi 9 bitovi postavljeni
    return;
  }

  uint8_t k;
  for (k = 0; k < 9; ++k) {
    if (possible & (1 << k))
      continue;

    map[i][j] = k + 1;
    row[i] |= 1 << k;
    col[j] |= 1 << k;
    sqr[(i / 3) * 3 + j / 3] |= 1 << k;
    // i know this will check the same square twice
    // but resolving that will add a lot of complexity
    solve(map, row, col, sqr, i + 1, j);

    map[i][j] = 0;
    row[i] &= ~(1 << k);
    col[j] &= ~(1 << k);
    sqr[(i / 3) * 3 + j / 3] &= ~(1 << k);
  }
}

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  alignas(64) uint8_t sudoku[9][9] = {{0, 0}};
  uint16_t row[9] = {0};
  uint16_t col[9] = {0};
  uint16_t sqr[9] = {0};

  // std::memset(sudoku, 0, sizeof(sudoku));
  // std::memset(row, 0, sizeof(row));
  // std::memset(col, 0, sizeof(col));
  // std::memset(sqr, 0, sizeof(sqr));

  uint8_t i, j;
  for (i = 0; i < 9; ++i)
    for (j = 0; j < 9; ++j) {
      char c;
      std::cin >> c;
      c -= 48; // covert ascii digit to binary
      if (c > 0) {
        sudoku[i][j] = c;
        --c;
        row[i] |= 1 << c;
        col[j] |= 1 << c;
        sqr[(i / 3) * 3 + j / 3] |= 1 << c;
      }
    }

  solve(sudoku, row, col, sqr, 0, 0);
}
