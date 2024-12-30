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

  uint32_t n, pom, max = 0;
  std::map<uint32_t, bool> elementi;

  std::cin >> n;

  for (uint32_t i = 0; i < n; ++i) {
    std::cin >> pom;
    if (elementi[pom] == 0)
      elementi[pom] = 1;
    else if (pom > max)
      max = pom;
  }

  if (max)
    std::cout << max;
  else
    std::cout << "nema";
}
