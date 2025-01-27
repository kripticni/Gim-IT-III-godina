#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);
  
  std::vector<uint32_t> arr;
  uint64_t r;
  uint32_t n, i;

  std::cin >> n;
  arr.reserve(n);

  for(i = 0; i < n; ++i){
    uint32_t pom;
    std::cin >> pom;
    arr.emplace_back(pom);
  }

  std::sort(arr.begin(), arr.end());

  r = 0;
  for(i = 0; i < n/2; ++i)
    r = std::max(r, (uint64_t)(arr[i] + arr[n - 1 - i])); 

  std::cout << r - 1;
}
