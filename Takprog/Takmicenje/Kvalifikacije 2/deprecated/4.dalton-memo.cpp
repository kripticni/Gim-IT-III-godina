#include <cstdint>
#include <cstring>
#include <iostream>

constexpr const uint32_t MAX_N = 10000;
constexpr const uint32_t MAX_M = 10000;
uint32_t N, M;
uint32_t a[MAX_N];
uint32_t arr[MAX_M];
int32_t memo[MAX_N][MAX_N];

[[gnu::hot]]
static uint32_t max(uint32_t a, uint32_t b) noexcept {
  return (a > b) ? a : b;
}

[[gnu::hot]]
static uint32_t min(uint32_t a, uint32_t b) noexcept {
  return (a < b) ? a : b;
}

[[gnu::hot]] [[gnu::pure]]
static uint32_t greedy(int32_t l, int32_t r, uint32_t korak, uint32_t itr) {
  if (l > r)
    return 0;

  if (memo[l][r] != -1)
    return memo[l][r];

  if (korak == itr)
    memo[l][r] = max(a[l] + greedy(l + 1, r, (korak + 1) % M, itr),
                     a[r] + greedy(l, r - 1, (korak + 1) % M, itr));
  else
    memo[l][r] = min(greedy(l + 1, r, (korak + 1) % M, itr),
                     greedy(l, r - 1, (korak + 1) % M, itr));

  return memo[l][r];
}

[[gnu::nothrow]] [[gnu::noinline]]
static void calc() noexcept {
  uint32_t i;
  for (i = 0; i < M; ++i) {
    std::memset(memo, -1, sizeof(memo));
    arr[i] = greedy(0, N - 1, 0, i);
  }
  for (i = 0; i < M; ++i)
    std::cout << arr[i] << ' ';

  return;
}

// inace ovo radim jer mi se svidja
// da ostane main samo za unos i za nista vise
// ali sam se tek sad setio za to
[[gnu::nothrow]]
int main() noexcept {
  std::cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  std::cin >> N >> M;
  uint32_t i;

  for (i = 0; i < N; ++i)
    std::cin >> a[i];

  calc();
}
