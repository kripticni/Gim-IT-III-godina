#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <map>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::map<std::string, int32_t> korisnici;
  std::map<int32_t, int32_t> racuni;

  uint32_t n, k;
  std::cin >> n >> k;
  racuni[0] = k; // JAKO BITNO da se nula inicializuje

  for (uint32_t i = 0; i < n; ++i) {
    std::string input;
    int32_t num;
    std::cin >> input >> num;

    if (input == "upit") {
      std::cout << racuni[num] << '\n';
    } else {
      --racuni[korisnici[input]];
      korisnici[input] += num;
      ++racuni[korisnici[input]];
    }
  }
}
