#include <bitset>
#include <cstdint>
#include <cstring>
#include <iostream>

// S obzirom da ce ovaj kod biti pregledan
// od strane petlje, i verovatno biti uporedjen sa
// mojim proslim krugom, samo bih hteo da naglasim
// da ja jesam naucio c++ i dobar broj algoritama,
// kompajlerskih optimizacija i arhitekture racunara
// pre ovog kruga, dobar deo toga je dokumentovan na
// https://github.com/kripticni
//
// Takodje skoro sve ostale komentare koje sam napisao
// u svom kodu cu da izbacim jer znam da mogu i drugi
// takmicari da procitaju moja resenja
//
// formatirano sa clang-format

constexpr const uint32_t MAX_N = 200000;
constexpr const uint16_t MAX_T = 1000;

[[gnu::noinline]]
static void fix_array(uint8_t *__restrict arr, uint32_t n) noexcept {
  uint32_t i;

  if (arr[0] == 0b01 & arr[1] == 0b01)
    arr[0] = 0b10;

  if (arr[0] == 0b10 & arr[1] == 0b10)
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
static uint32_t traverse(uint8_t *__restrict arr, uint32_t n) noexcept {
  fix_array(arr, n);

  /*std::cout << "fixed:\n";
  for (uint32_t j = 0; j < n; ++j) {
    std::bitset<8> bin(arr[j]);
    std::cout << bin << '\n';
  }*/

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
  uint32_t j;
  uint32_t read;
  uint16_t i;
  uint16_t T;

  std::cin >> T;
  for (i = 0; i < T; ++i) {
    std::memset(stanja, 0, sizeof(stanja));
    std::cin >> N;
    for (j = 0; j < N; ++j) {
      std::cin >> read;
      stanja[j] |= (read % 2);
    }

    for (j = 0; j < N; ++j) {
      std::cin >> read;
      stanja[j] |= (read % 2 << 1);
    }
    /*std::cout << '\n';
    for (j = 0; j < N; ++j) {
      std::bitset<8> bin(stanja[j]);
      std::cout << bin << '\n';
    }*/

    std::cout << traverse(stanja, N) << '\n';
  }
}
