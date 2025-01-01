#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <map>

// insert
// extract
// find

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::map<uint64_t, int64_t> madjionicari;
  uint64_t strength;
  char decide;

  while (std::cin >> decide) {
    switch (decide) {
    case 'i':
      std::cin >> strength;
      ++madjionicari[strength];
      break;
    case 'e':
      std::cin >> strength;
      --madjionicari[strength];
      if (madjionicari[strength] <= 0)
        madjionicari.erase(strength);
      break;
    case 'f':
      std::cin >> strength;
      const auto &itr = madjionicari.lower_bound(strength);
      if (itr == madjionicari.end())
        std::cout << "-\n";
      else
        std::cout << itr->first << '\n';
      break;
    }
  }
}
