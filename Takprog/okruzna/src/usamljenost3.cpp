#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::string arr;
  uint64_t br;
  uint32_t n, i, j;
  uint8_t m, f;
  bool rm, rmn, rmnn;

  std::cin >> n;
  arr.reserve(n);

  std::cin >> arr;
  
  br = 0;
  m = 0;
  f = 0;

  rm = false;
  rmn = false;
  rmnn = false;
  if(arr[0] == 'M'){ 
    ++m;
    rm = true;
  }
  else ++f;
  if(arr[1] == 'M'){
    ++m;
    rmn = true;
  }
  else ++f;
  if(arr[2] == 'M'){
    ++m;
    rmnn = true;
  }
  else ++f;
  if(m == 1 | f == 1) ++br;

  for(i = 3; i < n; ++i){
    if(rm) --m;
    else --f;

    rm = rmn;
    rmn = rmnn;

    switch(arr[i]){
      case 'M':{
        ++m;
        rmnn = true;
        break;
      }
      case 'F':{
        ++f;
        rmnn = false;
        break;
      }
      default:{
        ++f;
        rmnn = false;
        break;
      }
    }
  
    if(m==1 | f==1) ++br;
  }
  std::cout << br;
}
