#include <chrono>
#include <iostream>

int main() {
  constexpr int iterations = 10000000;
  constexpr int array_size = 5000;

  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; ++i) {
    uint32_t *arr = (uint32_t *)malloc(array_size * sizeof(uint32_t));
    free(arr);
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto malloc_duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "malloc time: " << malloc_duration.count() << " microseconds\n";

  start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; ++i) {
    uint32_t *arr = new uint32_t[array_size];
    delete[] arr;
  }
  end = std::chrono::high_resolution_clock::now();
  auto new_duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "new time: " << new_duration.count() << " microseconds\n";

  return 0;
}
