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

  std::vector<int32_t> a;
  std::vector<int32_t> b;
  uint16_t n, i, j, br;

  std::cin >> n;
  a.reserve(n);
  b.reserve(n);

  {
  int32_t pom; 
  for(i = 0; i < n; ++i){
    std::cin >> pom;
    a.emplace_back(pom);
  }
  for(i = 0; i < n; ++i){
    std::cin >> pom;
    b.emplace_back(pom);
  }
  }

  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  i = 0;
  j = 0;
  br = 0;

  while(i < n){
    if(a[i] < b[j]){
      ++i;
      continue;
    }
    ++i;
    ++j;
    ++br;
  }

  std::cout << br;
}
