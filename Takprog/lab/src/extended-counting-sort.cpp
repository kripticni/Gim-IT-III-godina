#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <random>

constexpr const int numInputs = 1000000;
constexpr int minRange = 0;
constexpr int maxRange = 100;

void extcsort(std::array<int, numInputs> &arr, int n) {
  std::array<int, maxRange - minRange> temp = {0};
  for (int val : arr)
    temp[val - minRange] = temp[val - minRange] + 1;

  long long int j = 0;
  for (int i = 0; i < maxRange - minRange; ++i)
    if (temp[i]) {
      // std::fill(arr.begin() + j, arr.begin() + j + temp[i], i);
      for (int k = 0; k < temp[i]; ++k)
        arr[j + k] = i + minRange;
      j += temp[i];
    }
  for (; j < n; ++j)
    arr[j] = maxRange;

  // for (auto &itr : arr)
  //   std::cout << itr << ' ';
  return;
}

int main() {

  std::random_device seed;
  std::mt19937 gen(seed()); // mersenne twister
  std::uniform_int_distribution<int> dist(minRange, maxRange);

  std::array<int, numInputs> inputs;
  for (int &input : inputs) {
    input = dist(gen);
  }

  std::array<int, numInputs> inputs1 = inputs;

  auto start = std::chrono::high_resolution_clock::now();
  std::sort(inputs1.begin(), inputs1.end());
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "std lib: " << duration.count() << " microseconds" << std::endl;

  // for (auto &itr : inputs1)
  //   std::cout << itr;

  start = std::chrono::high_resolution_clock::now();
  end = std::chrono::high_resolution_clock::now();
  extcsort(inputs, numInputs);
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "ext counting sort: " << duration.count() << " microseconds"
            << std::endl;

  return 0;
}
