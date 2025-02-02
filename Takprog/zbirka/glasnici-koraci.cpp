#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>
#include <cmath>

constexpr float diff = 1e-3;

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  float d, c, nx;
  uint32_t n, i = 0, s = 0;
  std::vector<float> arr;

  std::cin >> d >> n;
  arr = std::vector<float>(n);

  for(auto& itr : arr)
    std::cin >> itr;

  while(i < n){
    c = arr[i];
    nx = arr[i+1] - s;
    while(true){
      if(c + d > nx)
        break;
      else{
        nx -= 1;
        c += 1;
        ++s;
      }
    }
    ++i;
  }

  std::cout << std::fixed << std::showpoint
            << std::setprecision(3) << s;
}
