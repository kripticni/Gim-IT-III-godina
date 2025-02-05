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

  //std::vector<char> arr;
  std::vector<uint32_t> blk;
  uint64_t res;
  uint32_t n, i;
  char ch;
  bool s;

  std::cin >> n;
  //arr = std::vector<char>(n);

  std::cin >> ch;
  s = ch=='M'?true:false;
  blk.emplace_back(1);
  for(i = 1; i < n; ++i){
    std::cin >> ch;
    if(ch=='M'){
      if(s == true)
        ++blk.back();
      else{
        blk.emplace_back(1);
        s = true;
      }
    }else{
      if(s == false)
        ++blk.back();
      else{
        blk.emplace_back(1);
        s = false;
      }
    }
  }
  
  if (blk.size()==1)
  {
    std::cout<<0;
    return 0;
  }


  res = blk[1]-1;
  n = blk.size();
  for(i = 1; i < n - 1; ++i){
    if(blk[i] == 1)
      res+=(uint64_t)(blk[i-1]+1)*(blk[i+1]+1)-3;
    else
      res+=blk[i-1] + blk[i+1] - 2;
  }
  res+=blk[n-1]-1;
  std::cout << res;
}
