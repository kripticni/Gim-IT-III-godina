#include <bits/stdc++.h>
#include <random>

constexpr int MAX_SIZE = 10000000;

constexpr const int numInputs = 1000000;
// constexpr int minRange = 0; assuming its 0 anyways since its uint32
constexpr int maxRange = 2e3;

[[gnu::noinline]] [[gnu::hot]]
void extcsort(unsigned int *__restrict arr, int n) {
  int *__restrict temp = new int[maxRange];
  memset(temp, 0, (maxRange) * sizeof(int));

  int i;
  for (i = 0; i < n; ++i)
    temp[arr[i]] = temp[arr[i]] + 1;

  long long int j = 0;
  for (i = 0; i < maxRange; ++i)
    if (temp[i]) {
      for (int k = 0; k < temp[i]; ++k)
        arr[j + k] = i;
      j += temp[i];
    }
  for (; j < n; ++j)
    arr[j] = maxRange;

  return;
}

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

int main() {
  // std::random_device seed;
  std::mt19937 gen(43214); // mersenne twister
  std::uniform_int_distribution<int> dist(0, maxRange);

  int *inputs = new int[MAX_SIZE];

  for (int i = 0; i < MAX_SIZE; ++i)
    inputs[i] = dist(gen);

  uint32_t *inputs2 = new uint32_t[MAX_SIZE];
  std::memcpy(inputs2, inputs, MAX_SIZE * sizeof(uint32_t));
  uint32_t *inputs3 = new uint32_t[MAX_SIZE];
  std::memcpy(inputs3, inputs, MAX_SIZE * sizeof(uint32_t));

  auto start = std::chrono::high_resolution_clock::now();
  RadixSort256(inputs3, MAX_SIZE);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "r256: " << duration.count() << " microseconds" << '\n';

  start = std::chrono::high_resolution_clock::now();
  extcsort(inputs2, MAX_SIZE);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "extcsort: " << duration.count() << " microseconds" << '\n';
  return 0;
}
