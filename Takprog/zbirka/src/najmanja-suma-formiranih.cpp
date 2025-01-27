#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <math.h>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  uint64_t sum;
  uint8_t arr[30];
  uint8_t n, i;

  scanf("%hhu", &n);
  for(i = 0; i < n; ++i)
    scanf("%hhu", &arr[i]);

  sum = 0;
  uint8_t br_cifara = n/2 - 1;
  std::sort(arr, arr+n);

  i = 0;
  if(n%2 != 0){
    i = 1;
    sum += arr[0] * pow(10, br_cifara);
  }
  for(; i < n; i += 2){
    sum += arr[i] * pow(10, br_cifara); 
    sum += arr[i+1] * pow(10, br_cifara);
    --br_cifara;
  }
  
  printf("%lu", sum);
}
