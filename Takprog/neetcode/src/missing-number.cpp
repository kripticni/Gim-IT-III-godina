#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        uint32_t x = 0, y = 0;

        for(auto val : nums)
            x = x ^ val;

        for(uint64_t i = 0; i <= nums.size(); ++i)
            y = y ^ i;

        return x ^ y;
    }
};


int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);
}
