#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <set>
#include <unordered_map>

struct SetHasher {
  template <typename T> size_t operator()(const std::set<T> &s) const {
    size_t hash_val = 0;
    for (const auto &el : s) {
      hash_val ^=
          std::hash<T>()(el) + 0x9e3779b9 + (hash_val << 6) + (hash_val >> 2);
    }
    return hash_val;
  }
};

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::unordered_map<std::set<char>, uint16_t, SetHasher> reci(500);
  std::set<char> temp;
  std::string input;
  uint32_t n;
  uint32_t max = 0;

  std::cin >> n;
  for (uint32_t i = 0; i < n; ++i) {
    temp.clear();
    std::cin >> input;
    for (char &c : input)
      temp.emplace(c);

    ++reci[temp];
    if (reci[temp] > max)
      max = reci[temp];
  }
  std::cout << max;
}
