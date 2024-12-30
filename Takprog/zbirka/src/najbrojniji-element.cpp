#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <unordered_map>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::unordered_map<std::string, uint32_t> elementi;
  uint32_t n;

  std::cin >> n;
  uint32_t max = 0;
  for (uint32_t i = n; i != 0; --i) {
    std::string pom;
    std::cin >> pom;
    ++elementi[pom];
    if (elementi[pom] > max)
      max = elementi[pom];
  }
  std::cout << max;
}
