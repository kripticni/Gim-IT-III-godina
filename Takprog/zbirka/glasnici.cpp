#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdint>


int main() {
  std::vector<double> pozicije;
  uint32_t n, i;
  double domet, p, t = 0.0;

  std::cin >> domet >> n;
  pozicije = std::vector<double>(n);

  for(i = 0; i < n; i++)
    std::cin >> pozicije[i];

  p = pozicije[0];
  for (i = 1; i < n; i++) {
    if (pozicije[i] - t - p > domet) {
      t += (pozicije[i] - t - p - domet) / 2.0;
      p = pozicije[i] - t;
    } else {
      p = std::min(pozicije[i] + t, p + domet);
    }
  }

  std::cout << std::fixed << std::showpoint << std::setprecision(3)
       << t;

  return 0;
}
