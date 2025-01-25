#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <set> //brisanje iz vektora je O(n)

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::multiset<int32_t> arr;
  uint32_t br;
  int32_t n, i, j;

  std::cin >> n; //n moze da se izbrise jer se ne koristi dalje
  for(i = 0; i < n; ++i){
    int32_t pom;
    std::cin >> pom;
    arr.emplace(pom);
  }

  br = 0;
  while(!arr.empty()){
    auto itr = arr.begin();
    auto find = arr.lower_bound((*itr)*2);
    if(find != arr.end())
      ++br;
    arr.erase(itr);
  }
  std::cout << br;
}
