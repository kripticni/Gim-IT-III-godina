#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::vector<uint64_t> a, b, c;
  uint64_t t = 1;
  uint16_t n;
  uint16_t i2 = 0, i3 = 0, i5 = 0;
  
  std::cin >> n;
  a.emplace_back(2);
  b.emplace_back(3);
  c.emplace_back(5);

  for (int i = 0; i < n; ++i) {
    t = std::min({a[i2], b[i3], c[i5]});
    a.emplace_back(2*t);
    b.emplace_back(3*t);
    c.emplace_back(5*t);
    while (i2 < a.size() && a[i2] == t) i2++;
    while (i3 < b.size() && b[i3] == t) i3++;
    while (i5 < c.size() && c[i5] == t) i5++;
  }
  std::cout << t << '\n';
  return 0;
}
