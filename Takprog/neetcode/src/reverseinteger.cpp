#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <climits>

using namespace std;
class Solution {
  public:
    int reverse(int x){
        long long y = 0;
        while (x) {
            y = y * 10 + x % 10;
            x /= 10;
        }
        if (y < INT_MIN || y > INT_MAX)
            return 0;
        return y;
    }
};

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);
}
