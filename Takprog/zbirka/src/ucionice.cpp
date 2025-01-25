#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <tuple>
#include <vector>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::vector<std::pair<uint16_t, uint16_t>> arr;
  std::vector<uint16_t> end_time;
  uint32_t n, i;
  std::cin >> n;

  for(i = 0; i < n; ++i){
    std::pair<uint16_t, uint16_t> input;
    uint16_t pom;

    std::cin >> pom;
    input.first = pom*60;
    std::cin >> pom;
    input.first += pom;

    std::cin >> pom;
    input.second = pom*60;
    std::cin >> pom;
    input.second += pom;

    arr.emplace_back(input);
  }

  std::sort(arr.begin(), arr.end(), [](const std::pair<uint16_t, uint16_t>& a, const std::pair<uint16_t, uint16_t>& b) {
    return a.first < b.first; 
  });

  end_time.emplace_back(arr.begin()->second);
  for(auto& itr : arr){
    bool fit;
    fit = false;
    std::vector<uint16_t>::iterator end;
    for(end = end_time.begin(); end != end_time.end(); ++end){
      if(itr.first >= *end){
        fit = true;
        break;
      }
    }
    if(!fit){
      end_time.emplace_back(itr.second);
      *end = itr.second;
    }
  }

  std::cout << end_time.size();
}
