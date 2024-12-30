#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::vector<int64_t> takmicari;

  uint16_t n;
  std::cin >> n;

  uint64_t rezultat = 0;
  int64_t target;
  takmicari.reserve(n);

  for (uint16_t i = 0; i < n; ++i) {
    std::cin >> target;
    takmicari.emplace_back(target);
  }

  std::sort(takmicari.begin(), takmicari.end());
  for (uint16_t i = 0; i < n - 2; i++) {
    uint16_t l = i + 1;
    uint16_t r = n - 1;

    while (l < r) {
      int64_t suma = takmicari[i] + takmicari[l] + takmicari[r];
      if (suma == 0) {
        ++rezultat;
        ++l;
        --r;
      } else if (suma < 0)
        ++l;
      else
        --r;
    }
  }
  std::cout << rezultat;
}
