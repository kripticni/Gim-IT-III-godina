#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>

class Solution {
  public:
    int hammingWeight(uint32_t n){
      int br = 0;
      while(n){
        if(n&1)++br;
        n = n>>1;
      }
      return br;
    }
};

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);
}
