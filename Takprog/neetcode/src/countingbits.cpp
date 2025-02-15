#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

unsigned char bitsSetTable256[256];

void initialize() {
    bitsSetTable256[0] = 0;
  
    for (int i = 1; i < 256; i++) {
        bitsSetTable256[i] = (i & 1) + bitsSetTable256[i / 2];
    }
}

int countSetBits(int n) {
    return bitsSetTable256[n & 0xFF] + 
           bitsSetTable256[(n >> 8) & 0xFF] +
           bitsSetTable256[(n >> 16) & 0xFF] + 
           bitsSetTable256[(n >> 24) & 0xFF];
}

using namespace std;
class Solution{
  public:
    vector<int> countBits(int n){
      initialize();
      ++n;
      vector<int> sol = vector<int>(n);     
      for(int i = 0; i < n; ++i)
        sol[i] = countSetBits(i);
      return sol;
    }
};

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);
}
