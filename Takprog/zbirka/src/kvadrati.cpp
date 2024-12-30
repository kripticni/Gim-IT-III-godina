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

  int16_t rezultat = 0;
  int16_t diff = 0;
  std::set<int16_t> presek;

  for (auto itr1 = isti_y.begin(); itr1 != isti_y.end(); ++itr1) {
    // sve vrednosti iz isti_y.second su na isti y, treba nam za obe isti x
    for (auto itr2 = std::next(itr1); itr2 != isti_y.end(); ++itr2) {
      diff = std::abs(itr1->first - itr2->first);
      presek.clear();
      std::set_intersection(itr1->second.begin(), itr1->second.end(),
                            itr2->second.begin(), itr2->second.end(),
                            std::inserter(presek, presek.begin()));
      for (auto itr3 = std::next(presek.begin()); itr3 != presek.end(); ++itr3)
        if (*itr3 == *std::prev(itr3) + diff)
          ++rezultat;
    }
  }

  std::cout << rezultat;
}
