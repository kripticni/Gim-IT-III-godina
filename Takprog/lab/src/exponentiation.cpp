#include <chrono>
#include <iostream>
#include <random>
#include <vector>

long long rec_power(long long A, long long B) {
  if (B == 0)
    return 1;

  long long res = rec_power(A, B / 2);

  if (B % 2)
    return res * res * A;
  else
    return res * res;
}

long long power(long long a, long long b) {
  long long result = 1;
  while (b) {
    if (b & 1)
      result = result * a;
    a = a * a;
    b >>= 1;
  }
  // std::cout << result;
  return result;
}

int main() {
  constexpr long long int numInputs = 0x0fffffff;
  constexpr long long int minRange = 1;
  constexpr long long int maxRange = 2e9;

  std::random_device seed;
  std::mt19937 gen(seed()); // mersenne twister
  std::uniform_int_distribution<int> dist(minRange, maxRange);

  std::vector<long long int> inputs1(numInputs);
  for (long long int &input : inputs1) {
    input = dist(gen);
  }

  std::vector<long long int> inputs2(numInputs);
  for (long long int &input : inputs2) {
    input = dist(gen);
  }

  auto start = std::chrono::high_resolution_clock::now();
  for (long long int i = 0; i < numInputs; ++i) {
    std::pow(inputs1[i], inputs2[i]);
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "std lib: " << duration.count() << " microseconds" << std::endl;

  start = std::chrono::high_resolution_clock::now();
  for (long long int i = 0; i < numInputs; ++i) {
    power(inputs1[i], inputs2[i]);
  }
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "bin exp: " << duration.count() << " microseconds" << std::endl;
  return 0;
}
