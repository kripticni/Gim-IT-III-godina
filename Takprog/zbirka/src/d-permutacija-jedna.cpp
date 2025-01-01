#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  int32_t d, k;
  int32_t input;
  int16_t n;

  std::cin >> d >> k >> n;

  std::array<std::vector<int32_t>, 10> niz;

  for (int8_t i = 0; i < n; ++i) {
    for (int32_t j = 0; j < k; ++j) {
      std::cin >> input;
      niz[i].emplace_back(input);
    }
  }

  for (int16_t i = 1; i < n; ++i) {
    for (int32_t j = 0; j < k; ++j) {
      if (niz[0][j] == niz[i][j])
        continue;

      if (j - d >= 0)
        if (niz[0][j - d] == niz[i][j])
          continue;

      if (j + d < k)
        if (niz[0][j + d] == niz[i][j])
          continue;

      goto skip;
    }
    std::cout << "da\n";
    continue;
  skip:
    std::cout << "ne\n";
    continue;
  }
}
