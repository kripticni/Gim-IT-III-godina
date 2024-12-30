#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <set>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::multiset<uint32_t> parovi;
  uint32_t n;

  std::cin >> n;
  for (auto i = n; i != 0; --i) {
    uint32_t pom;
    std::cin >> pom;
    parovi.insert(pom);
  }

  std::multiset<uint32_t>::iterator itr = parovi.begin();
  while (itr != parovi.end()) {
    if (*itr == *std::next(itr)) {
      itr = std::next(itr, 2);
      continue;
    }
    std::cout << *itr;
    return 0;
  }
  std::cout << -1;
}
