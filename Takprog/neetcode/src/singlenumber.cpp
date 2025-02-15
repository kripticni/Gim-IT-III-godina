#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
  int singleNumber(std::vector<int>& nums) {
    int x = 0;
    for(auto& itr: nums)
      x = x ^ itr;
    return x;
  }
};

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

}
