#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

[[gnu::always_inline]] [[gnu::const]]
static inline uint32_t next_pow2(uint32_t x) { 	
  x -= 1;
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	
	return x + 1;
};

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::vector<uint32_t> arr;
  std::vector<uint32_t> sol;
  uint32_t n, i, mask;
  uint8_t t, e;

  std::cin >> n;
  t = n;

  for(e = 0; e < t; ++e){
    std::cin >> n;
    arr = std::vector<uint32_t>(n+1);
    sol = std::vector<uint32_t>(n+1);

    for(i = 0; i < n+1; ++i)
      std::cin >> arr[i];

    for(i = 0; i < n+1; ++i){
      mask = (arr[i]!=0)?next_pow2(arr[i]):`;
      mask = mask | (mask-1);
      sol[i] = arr[i] ^ mask;
    }

    for(i = 0; i < n+1; ++i)
      std::cout << sol[i] << ' ';
  }
}
