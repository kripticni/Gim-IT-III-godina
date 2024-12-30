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

  uint32_t n, rezultat = 0;
  uint64_t s, pom;
  std::multiset<uint64_t> niz;

  std::cin >> s >> n;
  for (uint32_t i = 0; i < n; ++i) {
    std::cin >> pom;
    niz.emplace(pom);
  }

  std::multiset<uint64_t>::iterator left = niz.begin();
  // std::multiset<uint64_t>::reverse_iterator right = niz.rbegin();
  std::multiset<uint64_t>::iterator right = std::prev(niz.end());
  while (left != right) {
    if (*left + *right > s) {
      --right;
      continue;
    }
    if (*left + *right < s) {
      ++left;
      continue;
    }

    ++rezultat;

    --right;
    ++left;
  }
  std::cout << rezultat;
}
