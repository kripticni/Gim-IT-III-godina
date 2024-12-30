/*
We are given two arrays num[0..k-1] and rem[0..k-1]. In num[0..k-1],
every pair is coprime (gcd for every pair is 1).
We need to find minimum positive number x such that:

     x % num[0]    =  rem[0],
     x % num[1]    =  rem[1],
     .......................
     x % num[k-1]  =  rem[k-1]
*/
#include <iostream>

int findMinX(int num[], int rem[], int k) {
  int x = 1;

  // this has to always break
  while (true) {
    int j;
    for (j = 0; j < k; j++)
      if (x % num[j] != rem[j])
        break;

    if (j == k)
      return x;

    x++;
  }

  return x;
}

int main() {
  int num[] = {3, 4, 5};
  int rem[] = {2, 3, 1};
  int k = sizeof(num) / sizeof(num[0]);
  std::cout << "x is " << findMinX(num, rem, k);
  return 0;
}
