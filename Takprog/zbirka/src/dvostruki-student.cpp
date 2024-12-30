#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <map>
#include <string>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  // std::array<std::string, 50000> studenti;
  std::map<std::string, bool> studenti;
  while (1) {
    std::string pom;
    std::getline(std::cin, pom);
    if (studenti[pom] == 1) {
      std::cout << pom;
      return 0;
    }
    studenti[pom] = 1;
  }
}
