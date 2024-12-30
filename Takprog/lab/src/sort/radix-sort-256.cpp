#include <bits/stdc++.h>

static void RadixSort256(unsigned int *__restrict arr, int n) {
  if (n <= 1)
    return; // base case

  unsigned int *__restrict output = new unsigned int[n]; // output array
  int *count = new int[256];                             // base 256
  unsigned int *originalArr = arr; // so we know what to return

  for (int shift = 0, s = 0; shift < 4; shift++, s += 8) {
    // zero out the arr
    // for (int i = 0; i < 256; i++)
    // count[i] = 0;
    memset(count, 0, 256 * sizeof(int));

    // count
    for (int i = 0; i < n; ++i)
      count[(arr[i] >> s) & 0xff]++;

    // prefix sum
    for (int i = 1; i < 256; ++i)
      count[i] += count[i - 1];

    // reconstruct the array
    for (int i = n - 1; i >= 0; --i) {
      // precalculate the offset as it's a few instructions
      int idx = (arr[i] >> s) & 0xff;

      // store and decrement the count
      output[--count[idx]] = arr[i];
    }

    // Copy the output array to input[], so that input[]
    // is sorted according to current digit
    // We can just swap the pointers
    // unsigned int* tmp = arr;
    // arr = output;
    // output = tmp;
    arr = (unsigned int *)((uintptr_t)arr ^ (uintptr_t)output);
    output = (unsigned int *)((uintptr_t)arr ^ (uintptr_t)output);
    arr = (unsigned int *)((uintptr_t)arr ^ (uintptr_t)output);
  }

  // If we switched pointers an odd number of times,
  // make sure we copy before returning
  if (originalArr == output) {
    // unsigned int* tmp = arr;
    // arr = output;
    // output = tmp;
    arr = (unsigned int *)((uintptr_t)arr ^ (uintptr_t)output);
    output = (unsigned int *)((uintptr_t)arr ^ (uintptr_t)output);
    arr = (unsigned int *)((uintptr_t)arr ^ (uintptr_t)output);

    // for (int i = 0; i < n; i++)
    //  arr[i] = output[i];
    memcpy(arr, output, n * sizeof(int));
  }

  delete[] output;
  delete[] count;
}

int main() {
  unsigned int arr[] = {32,  23, 1542, 214, 51, 2131, 213123,
                        123, 1,  2423, 324, 42, 2,    3};
  RadixSort256(arr, sizeof(arr) / sizeof(int));
  for (int i = 0; i < (int)(sizeof(arr) / sizeof(int)); ++i)
    std::cout << arr[i] << ' ';
}
