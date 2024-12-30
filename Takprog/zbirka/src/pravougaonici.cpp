#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  uint16_t n;
  std::map<int16_t, std::set<int16_t>> isti_y;

  std::cin >> n;
  for (uint16_t i = 0, x, y; i < n; ++i) {
    std::cin >> x >> y;
    isti_y[y].emplace(x);
  }

  std::set<int16_t> presek;
  int16_t rezultat = 0;
  for (auto itr1 = isti_y.begin(); itr1 != isti_y.end(); ++itr1) {
    // sve vrednosti iz isti_y.second su na isti y, treba nam za obe isti x
    for (auto itr2 = std::next(itr1); itr2 != isti_y.end(); ++itr2) {
      presek.clear();
      std::set_intersection(itr1->second.begin(), itr1->second.end(),
                            itr2->second.begin(), itr2->second.end(),
                            std::inserter(presek, presek.begin()));
      if (presek.size() > 1)
        rezultat += (presek.size() - 1) * presek.size() / 2;
    }
  }

  std::cout << rezultat;
}
