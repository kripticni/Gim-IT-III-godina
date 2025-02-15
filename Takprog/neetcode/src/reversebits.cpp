#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>

class Solution {
  public:
    uint32_t reverseBits(uint32_t n){
      uint32_t sol = 0;
      for(int i = 0; i < 32; ++i)
        sol |= ((n >> i) & 1) << (31 - i);
      return sol;
    }
};

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);
}
