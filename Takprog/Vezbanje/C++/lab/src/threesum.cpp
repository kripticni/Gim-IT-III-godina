#include <algorithm>
#include <array>
#include <iostream>

int main() {
  std::cin.tie(NULL);
  std::ios::sync_with_stdio(false);

  int n;
  std::cin >> n;

  int arr[1024]; // instead of VLA or vectors
  // std::array<int, 1024> arr;
  int i;
  for (i = 0; i < n; ++i)
    std::cin >> arr[i];

  int target;
  std::cin >> target;

  std::sort(arr, arr + n);
  /*
  for (i = 0; i < n; ++i)
    std::cout << arr[i];
  */
  {

    int *l;
    int *r;
    int *m;
    // int cache;

    for (m = arr; m < arr + n - 2; ++m) {
      l = m + 1;
      r = arr + n - 1;

      while (l < r) {
        // cache = *l + *r + *i; //actually no need, since this will just use
        // two conditional jumps and a cmp anyways
        if (*l + *r + *m == target) {
          // std::cout << (l - arr) << ' ' << (m - arr) << ' ' << (r - arr);
          // gives indexes of the sorted array
          std::cout << *l << ' ' << *m << ' ' << *r;
          return 0;
        }
        if (*l + *r + *m > target)
          --r;
        else
          ++l;
      }
    }
  }
  /* this honestly feels awful to do in the c++ way
  auto l = arr.begin();
  auto r = arr.end();
  std::array<int,1024>::iterator m;
  while(l < r){
    int cache = *l + *r;
    if(target < cache){
      if( cache + *(std::next(l)) == target){
        std::cout << std::distance(arr.begin(), l) << ' ' <<
  std::distance(arr.begin(), l + 1) << ' ' << std::distance(arr.begin(), r);
        return 0;
      }else{
        if( cache + *(std::prev(r)) == target){
          std::cout << std::distance(arr.begin(), l) << ' ' <<
  std::distance(arr.begin(), r - 1) << ' ' << std::distance(arr.begin(), r);
          return 0;
        }
      }
    }
  }
  */
}
