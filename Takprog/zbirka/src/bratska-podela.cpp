#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <set>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::multiset<float> predmeti;
  float ins;
  uint16_t n, i;

  std::cin >> n;
  for (i = 0; i < n; ++i) {
    std::cin >> ins;
    predmeti.emplace(ins);
  }

  while (predmeti.size() > 2) {
    ins = *predmeti.begin() + *std::next(predmeti.begin());
    predmeti.erase(predmeti.begin());
    predmeti.erase(predmeti.begin());
    predmeti.emplace(ins);
  }

  std::cout << std::fixed << std::setprecision(2)
            << *std::next(predmeti.begin()) - *predmeti.begin();
}
