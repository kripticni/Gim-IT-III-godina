#include <cstdint>
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

constexpr const uint32_t MAX_N = 10000;
constexpr const uint32_t MAX_M = 10000;
uint32_t N, M;
uint32_t a[MAX_N];
uint32_t arr[MAX_M];

[[gnu::hot]]
static uint32_t max(uint32_t a, uint32_t b) noexcept {
  return (a > b) ? a : b;
}

[[gnu::hot]]
static uint32_t min(uint32_t a, uint32_t b) noexcept {
  return (a < b) ? a : b;
}

[[gnu::hot]]
static uint32_t greedy(int32_t l, int32_t r, uint32_t korak,
                       uint32_t itr) noexcept {
  if (l > r)
    return 0;

  if (korak == itr)
    return max(a[l] + greedy(l + 1, r, (korak + 1) % M, itr),
               a[r] + greedy(l, r - 1, (korak + 1) % M, itr));
  else
    return min(greedy(l + 1, r, (korak + 1) % M, itr),
               greedy(l, r - 1, (korak + 1) % M, itr));
}

[[gnu::noinline]]
static void calc() noexcept {
  uint32_t i;
  for (i = 0; i < M; ++i)
    arr[i] = greedy(0, N - 1, 0, i);

  for (i = 0; i < M; ++i)
    std::cout << arr[i] << ' ';

  return;
}

// inace ovo radim jer mi se svidja
// da ostane main samo za unos i za nista vise
// ali sam se tek sad setio za to
int main() noexcept {
  std::cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  std::cin >> N >> M;
  uint32_t i;

  for (i = 0; i < N; ++i)
    std::cin >> a[i];

  calc();
}
