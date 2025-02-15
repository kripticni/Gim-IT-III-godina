#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>


using namespace std;
class Solution {
  public:
    int getSum(int a, int b){
      bool carry = 0;
      for(uint8_t i = 0; i < 32; ++i){
        uint8_t l, r, calc;
        l = isSet(a,i);
        r = isSet(b,i);
        calc = l + r + carry;
        switch(calc){
          case 0:
            break;
          case 1:
            set(a,i);
            if(carry) carry = false;
            break;
          case 2:
            unset(a,i);
            carry = true;
            break;
          case 3:
            set(a,i);
            carry = true;
            break;
        }
      }
      return a;
  }
  private:
    bool isSet(int32_t value, uint8_t index){
      return (value >> index) & 1;
    }
    void set(int32_t& value, uint8_t index){
      value |= 1 << index;
    }
    void unset(int32_t& value, uint8_t index){
      value &= ~(1 << index);
    }
};

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);
}
