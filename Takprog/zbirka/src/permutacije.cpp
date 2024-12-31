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

  std::map<int32_t, int32_t> permutacija;
  int32_t input;
  uint32_t n1, n2;

  std::cin >> n1;
  for (uint32_t i = 0; i < n1; ++i) {
    std::cin >> input;
    ++permutacija[input];
  }

  std::cin >> n2;
  if (n2 != n1) {
    std::cout << "ne";
    return 0;
  }

  for (uint32_t i = 0; i < n1; ++i) {
    std::cin >> input;
    --permutacija[input];
  }

  for (auto &itr : permutacija)
    if (itr.second != 0) {
      std::cout << "ne";
      return 0;
    }

  std::cout << "da";
}
