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
  uint32_t n, i, j, sum;

  std::cin >> n;
  arr.reserve(n);
  
  for(i = 0; i < n; ++i){
    uint32_t pom;
    std::cin >> pom;
    arr.emplace_back(pom);
  }

  std::sort(arr.begin(), arr.end());

  sum = 0;
  i = 0;
  j = n - 1;
  while(i < j){
    sum += arr[j] - arr[i];
    ++i;
    sum += arr[j] - arr[i];
    --j;
  }
  sum += arr[i] - arr[0];

  std::cout << sum;
}
