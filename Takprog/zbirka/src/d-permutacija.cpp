#include <algorithm>
#include <cstdint>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::map<int32_t, std::deque<int32_t>> niz;
  std::map<int32_t, std::deque<int32_t>> kopija;
  int32_t d, k, input;
  int16_t n;

  std::cin >> d >> k >> n;

  for (int32_t j = 1; j <= k; ++j) {
    std::cin >> input;
    niz[j % d].emplace_back(input);
  }

  /*
  for (auto itr = niz.begin(); itr != niz.end(); ++itr) {
    std::cout << "\n" << itr->first << "\n";
    for (auto itr1 : itr->second)
      std::cout << itr1;
  }
  */

  bool stanje;
  for (int16_t i = 1; i < n; ++i) {
    stanje = 1;
    kopija = niz;
    for (int32_t j = 1; j <= k; ++j) {
      std::cin >> input;
      if (stanje) {
        auto itr = std::find(kopija[j % d].begin(), kopija[j % d].end(), input);

        if (itr != kopija[j % d].end())
          kopija[j % d].erase(itr);
        else {
          stanje = 0;
        }
      }
    }
    if (stanje)
      std::cout << "da\n";
    else
      std::cout << "ne\n";
  }
}
