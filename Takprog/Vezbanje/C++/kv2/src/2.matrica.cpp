#include <bitset>
#include <cstdint>
#include <cstring>
#include <iostream>

constexpr const uint32_t MAX_N = 200000;
constexpr const uint16_t MAX_T = 1000;

/*[[gnu::always_inline]]
static void swap(uint32_t &__restrict a, uint32_t &__restrict b) {
  a = a ^ b;
  b = a ^ b;
  a = a ^ b;
}*/

[[gnu::noinline]]
// 00 parno-parno, 11 neparno-neparno, 01 parno-neparno, 10 neparno-parno
static void fix_array(uint8_t *__restrict arr, uint32_t n) noexcept {
  uint32_t i;

  if ((arr[0] == 0b01) & (arr[1] == 0b01 | arr[1] == 0b11))
    arr[0] = 0b10;

  if ((arr[0] == 0b10) & (arr[1] == 0b10 | arr[1] == 0b00))
    arr[0] = 0b01;

  for (i = 0; i < n - 1; ++i) {
    if (arr[i] == 0b01 & arr[i + 1] == 0b01) {
      arr[i + 1] = 0b10;
      continue;
    }
    if (arr[i] == 0b10 & arr[i + 1] == 0b10) {
      arr[i + 1] = 0b01;
      continue;
    }
    if (arr[i] == 0b00 & arr[i + 1] == 0b01) {
      arr[i + 1] = 0b10;
      continue;
    }
    if (arr[i] == 0b11 & arr[i + 1] == 0b10)
      arr[i + 1] = 0b01;
  }
}

[[gnu::hot]] [[gnu::noinline]]
uint32_t traverse(uint8_t *__restrict arr, uint32_t n) noexcept {
  // moze zameniti bilo koji broj polja
  // polja se menjaju izkljucivo kao A[i][0] A[i][1]
  fix_array(arr, n);

  // std::cout << "fixed:\n";
  // for (uint32_t j = 0; j < n; ++j) {
  //   std::bitset<8> bin(arr[j]);
  //   std::cout << bin << '\n';
  // }

  uint32_t i;
  uint32_t sum = 0;
  for (i = 0; i < n - 1; ++i) {
    if (arr[i] == 0b00) {
      ++sum;
      if (arr[i + 1] == 0b10 | arr[i + 1] == 0b00)
        ++sum;
      continue;
    }
    if (arr[i] == 0b11) {
      ++sum;
      if (arr[i + 1] == 0b01 | arr[i + 1] == 0b11)
        ++sum;
      continue;
    }
    if (arr[i] == 0b01) {
      if (arr[i + 1] == 0b10 | arr[i + 1] == 0b00)
        ++sum;
      continue;
    }
    // if arr[i] == 0b10
    if (arr[i + 1] == 0b01 | arr[i + 1] == 0b11)
      ++sum;
  }
  if (arr[i] == 0b00 | arr[i] == 0b11)
    ++sum;

  return sum;
}

int main() noexcept {
  std::cin.tie(NULL);
  std::ios::sync_with_stdio(false);

  uint32_t N;
  uint8_t stanja[MAX_N];
  // uint32_t A[MAX_T][MAX_N][2]; //redukuj MAX_T
  uint32_t j; // 200000
  uint32_t read;
  uint16_t i; // 1000
  uint16_t T;

  // mozda mogu da citam jedan po jedan primer, i da onda resavam
  // i ispisujem u stdout, lakse za cache i manje memorije zauzima
  std::cin >> T;
  for (i = 0; i < T; ++i) {
    std::memset(stanja, 0, sizeof(stanja));
    std::cin >> N;
    for (j = 0; j < N; ++j) {
      // std::cin >> A[i][j][0];
      std::cin >> read;
      stanja[j] |= (read % 2); // 0 parno, 1 neparno
    }

    for (j = 0; j < N; ++j) {
      // std::cin >> A[i][j][1];
      std::cin >> read;
      stanja[j] |= (read % 2 << 1); // 00 parno-parno, 11 neparno-neparno, 01
                                    // parno-neparno, 10 neparno-parno
    }
    /*std::cout << '\n';
    for (j = 0; j < N; ++j) {
      std::bitset<8> bin(stanja[j]);
      std::cout << bin << '\n';
    }*/

    std::cout << traverse(stanja, N) << '\n';
  }
}
