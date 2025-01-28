#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <queue>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::vector<std::deque<uint8_t>> vec;
  std::deque<uint8_t> a;
  std::deque<uint8_t> b;
  uint32_t t;
  uint16_t n, i;

  std::cin >> n;
  vec.reserve(n);
  for(i = 0; i < n; ++i){
    std::cin >> t;

    vec.emplace_back();
    vec[i].clear();
    while(t){
      vec[i].emplace_front(t%10);
      t /= 10;
    }
  }
  std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
  });

  for(auto itr = vec.begin(); itr != vec.end(); ++itr){
    auto rit = (*itr).rbegin();
    for(; rit != (*itr).rend(); ++rit)
      b.push_front(*rit);

    auto it = (*itr).begin();
    for(; it != (*itr).end(); ++it)
      a.push_back(*it);

    if(std::lexicographical_compare(a.begin(), a.end(),
                                    b.begin(), b.end()))
      b = std::deque<uint8_t>(a.begin(),a.end());
    else
      a = std::deque<uint8_t>(b.begin(),b.end());
  }

  for(auto itr = a.begin(); itr != a.end(); ++itr)
    std::cout << (uint16_t)*itr;
}

/*
    auto itr1 = a.begin();
    auto itr2 = b.begin();
    while(itr1 != a.end() && itr2 != b.end()){
      if(*itr1 == *itr2){ [[unlikely]]
        ++itr1;
        ++itr2;
        continue;
      }
      
      if(*itr1 < *itr2)
        std::copy(a.begin(), a.end(), b.begin());
      else
        std::copy(b.begin(), b.end(), a.begin());

      break;
    }
*/
