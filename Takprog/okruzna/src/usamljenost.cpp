#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::string arr;
  std::vector<uint32_t> pref;
  uint64_t br = 0;
  uint32_t n, i = 0, j;
  int32_t k;

  std::cin >> n;
  arr.reserve(n);

  std::cin >> arr;

  while(i < n){
    if(arr[i] == 'M'){
      j = i;
      k = i;
      while(arr[j+1] == 'F' && j < n){++j;}
      while(arr[k-1] == 'F' && k > 0){--k;}
      k = i - k;
      j = j - i;

      if(k > 0 && j > 0)
        br += k*j;
      if(k > 1 && j < 2)
        br += k - 1;
      if(j > 1 && k < 2)
        br += j - 1;

      i = std::max(j, i+1);
    }else{
      if(arr[i] == 'F'){
        j = i;
        k = i;
        while(arr[j+1] == 'M' && j < n){++j;}
        while(arr[k-1] == 'M' && k > 0){--k;}
        k = i - k;
        j = j - i;

        if(k > 0 && j > 0)
          br += k*j;
        if(k > 1 && j < 2)
          br += k - 1;
        if(j > 1 && k < 2)
          br += j - 1;

        i = std::max(i+1,j);
      }
    }
  }

  std::cout << br;
}

