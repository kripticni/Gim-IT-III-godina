#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

constexpr const int MAX_N = 10000;

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  uint32_t n;
  std::unordered_set<uint32_t> adrese;

  std::cin >> n;
  for (uint32_t i = n, pom; i != 0; --i) {
    std::cin >> pom;
    adrese.insert(pom);
  }

  std::cout << adrese.size();
}
