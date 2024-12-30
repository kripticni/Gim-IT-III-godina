#include <iostream>
#include <stdint.h>
#include <string.h>

constexpr int MAX_SIZE = 1024;

int nDigits(int n) {
  int digits = 0;
  while (n > 0) {
    n /= 10;
    ++digits;
  }
  return digits;
}

int retMax(int arr[], int n) {
  int max = arr[n];
  for (; n > 0; --n)
    if (arr[n] > max)
      max = arr[n];
  return max;
}

static inline void countSort(int arr[], int n, int exp) {
  int output[MAX_SIZE];
  int i, count[10] = {0};

  for (i = n - 1; i >= 0; --i)
    ++count[(arr[i] / exp) % 10];
  // count

  for (i = 1; i < 10; ++i)
    count[i] += count[i - 1];
  // prefix

  for (i = n - 1; i >= 0; --i) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }
  // reconstruct

  for (i = 0; i < n; i++)
    arr[i] = output[i];
  // memcpy(arr, output, n);
}

void radixSort(int arr[], int n) {
  int m = nDigits((uint64_t)retMax(arr, n));

  for (int exp = 1; m >= 0; --m, exp *= 10)
    countSort(arr, n, exp);
}

int main() {
  std::cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int arr[] = {40, 23, 11, 3, 4, 5, 170, 45, 75, 90, 802, 24, 2, 66};
  int n = sizeof(arr) / sizeof(arr[0]);

  radixSort(arr, n);
  for (int i = 0; i < n; i++)
    std::cout << arr[i] << " ";
  return 0;
}
