#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

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

  std::priority_queue<uint32_t> min;
  auto it_b = a.begin();
  auto it_a = b.begin();
  auto beg_a = a.begin();
  auto beg_b = b.begin();
  auto temp = b.begin();
  
  while(std::get<0>(*it_a) == std::get<0>(*it_b) &&
        it_a != a.end() && it_b != b.end()){
      ++it_a;
      ++it_b;
  }

  while(std::get<0>(*it_a) == std::get<0>(*(it_a - 1)) && it_a != a.end())
    ++it_a;

  while(std::get<0>(*it_b) == std::get<0>(*(it_b - 1)) && it_b != b.end())
    ++it_b;

  std::sort(beg_a, it_a, [](const auto& a, const auto& b){
    return std::get<1>(a) < std::get<1>(b);
  });
  std::sort(beg_b, it_b, [](const auto& a, const auto& b){
    return std::get<1>(a) < std::get<1>(b);
  });

  if(it_a - beg_a > it_b - beg_b){
    while(beg_b != it_b + 1){
      if( (temp = std::upper_bound(beg_a, it_a, *beg_b)) == it_a+1 ){
        std::cout << '-';
        return 0;
      }
      --temp;
      std::swap(beg_a, temp);
      ++beg_b;
    }
  } else {
    while(beg_a != it_a + 1){
      if( (temp = std::upper_bound(beg_b, it_b, *beg_a)) == it_b+1 ){
        std::cout << '-';
        return 0;
      }
      --temp;
      std::swap(beg_b, temp);
      ++beg_a;
    }
  }

  //separate by segments of same color
  //it_a shows a segment of same colored books in a row
  //it_b shows a segment of same colored books in b row
  //this is much simpler in C, ill do it in C tmrw

}
