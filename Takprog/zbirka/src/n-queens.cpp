#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <utility>
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma GCC optimize("O3")

[[gnu::hot]] [[gnu::noinline]]
static void backtrack(uint8_t (&queen)[11], bool (&row)[11], bool (&col)[11],
                      bool (&main)[22], bool (&side)[22], const uint8_t j,
                      const uint8_t N) noexcept {
  uint8_t i;
  if (j > N) {
    for (i = 0; i <= N; ++i)
      std::cout << (uint16_t)queen[i] << ' ';

    std::cout << '\n';
    return;
  }

  for (i = 0; i <= N; ++i) {
    if (row[i] | col[j] | side[i + j] | main[i - j + N]) [[unlikely]]
      continue;

    row[i] = true;
    col[j] = true;
    side[i + j] = true;
    main[i - j + N] = true;
    queen[j] = i + 1;

    backtrack(queen, row, col, main, side, j + 1, N);

    row[i] = false;
    col[j] = false;
    side[i + j] = false;
    main[i - j + N] = false;
  }
}

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  // bool tabla[11][11];
  alignas(64) uint8_t queens[11];
  bool row[11];
  bool col[11];
  bool diag1[22];
  bool diag2[22];

  std::memset(queens, 0, sizeof(queens));
  std::memset(row, 0, sizeof(row));
  std::memset(col, 0, sizeof(col));
  std::memset(diag1, 0, sizeof(diag1));
  std::memset(diag2, 0, sizeof(diag2));

  uint8_t N;
  {
    uint16_t n;
    std::cin >> n;
    N = (uint8_t)n; // keeping the max
    --N;            // most operations just decrement it anyways
  } // deleting the n after input
  backtrack(queens, row, col, diag1, diag2, 0, N);
}
