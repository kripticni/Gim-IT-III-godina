#include <bits/stdc++.h>
#include <random>

constexpr int MAX_SIZE = 10000000;

[[gnu::noinline]] [[gnu::hot]]
static void RadixSort256(unsigned int *__restrict arr, int n) {
  // if (n <= 1)
  //   return; // base case

  unsigned int *__restrict output = new unsigned int[n]; // output array
  int count[256];                                        // base 256
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
}

[[gnu::noinline]] [[gnu::hot]]
int nDigits(int n) {
  int digits = 0;
  while (n > 0) {
    n /= 10;
    ++digits;
  }
  return digits;
}

[[gnu::noinline]] [[gnu::hot]]
int retMax(int arr[], int n) {
  int max = arr[n];
  for (; n > 0; --n)
    if (arr[n] > max)
      max = arr[n];
  return max;
}

[[gnu::always_inline]] [[gnu::hot]]
static inline void countSort(int arr[], int n, int exp) {
  int *output = new int[MAX_SIZE];
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

[[gnu::noinline]] [[gnu::hot]]
void radixSort(int arr[], int n) {
  int m = nDigits((uint64_t)retMax(arr, n));

  for (int exp = 1; m >= 0; --m, exp *= 10)
    countSort(arr, n, exp);
}

int main() {
  // std::random_device seed;
  std::mt19937 gen(43214); // mersenne twister
  std::uniform_int_distribution<int> dist(0, (int)2e9);

  int *inputs = new int[MAX_SIZE];

  for (int i = 0; i < MAX_SIZE; ++i)
    inputs[i] = dist(gen);

  int *inputs2 = new int[MAX_SIZE];
  std::memcpy(inputs2, inputs, MAX_SIZE * sizeof(int));
  uint32_t *inputs3 = new uint32_t[MAX_SIZE];
  std::memcpy(inputs3, inputs, MAX_SIZE * sizeof(int));

  auto start = std::chrono::high_resolution_clock::now();
  std::sort(inputs, inputs + MAX_SIZE);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "std lib: " << duration.count() << " microseconds" << '\n';

  // for (auto &itr : inputs1)
  //   std::cout << itr;

  start = std::chrono::high_resolution_clock::now();
  radixSort(inputs2, MAX_SIZE);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "radix sort: " << duration.count() << " microseconds" << '\n';

  start = std::chrono::high_resolution_clock::now();
  RadixSort256(inputs3, MAX_SIZE);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "r256 sort: " << duration.count() << " microseconds" << '\n';
  return 0;
}
