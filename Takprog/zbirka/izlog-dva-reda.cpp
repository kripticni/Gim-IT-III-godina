#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>
#include <tuple>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::vector<std::tuple<uint32_t, uint32_t, uint16_t>> a;
  std::vector<std::tuple<uint32_t, uint32_t, uint16_t>> b;
  uint16_t n, i;

  std::cin >> n;
  a = std::vector<std::tuple<uint32_t, uint32_t, uint16_t>>(n);
  b = std::vector<std::tuple<uint32_t, uint32_t, uint16_t>>(n);

  for(i = 0; i < n; ++i)
    std::cin >> std::get<0>(a[i]);
  for(i = 0; i < n; ++i)
    std::cin >> std::get<1>(a[i]);
  for(i = 0; i < n; ++i)
    std::cin >> std::get<0>(b[i]);
  for(i = 0; i < n; ++i)
    std::cin >> std::get<1>(b[i]);

  for(i = 0; i < n; ++i){
    std::get<2>(a[i]) = i + 1;
    std::get<2>(b[i]) = i + 1;
  }

  //prednji red > zadnji red
  //a = zadnji, b = prednji
  //a.second > b.second
  
  std::sort(a.begin(), a.end(), [](const auto& a, const auto& b){
    return std::get<0>(a) < std::get<0>(b);
  });

  std::sort(b.begin(), b.end(), [](const auto& a, const auto& b){
    return std::get<0>(a) < std::get<0>(b);
  });

  auto it_b = a.begin();
  auto it_a = b.begin();
  
  while(std::get<0>(*it_a) == std::get<0>(*it_b) &&
        it_a != a.end() && it_b != b.end()){
      ++it_a;
      ++it_b;
  }
  if(it_a + 1 != a.end())
    if(std::get<0>(*(it_a + 1)) == std::get<0>(*(it_a))){
      std::cout << '-';
      return 0;
    }
  if(it_b + 1 != b.end())
    if(std::get<0>(*(it_b + 1)) == std::get<0>(*(it_b))){
      std::cout << '-';
      return 0;
    }
  //separate by segments of same color

}
