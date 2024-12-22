#include <cstdint>
#include <cstring>
#include <iostream>

constexpr const int MAX_N = 10000;
constexpr const int MAX_M = 10000;
uint32_t a[MAX_N];

[[gnu::always_inline]]
static uint32_t max(uint32_t a, uint32_t b) noexcept {
  return (a > b) ? a : b;
}

[[gnu::always_inline]]
static uint32_t min(uint32_t a, uint32_t b) noexcept {
  return (a < b) ? a : b;
}

struct return_struct {
  uint32_t l;
  uint32_t r;
};

[[gnu::hot]] [[gnu::pure]]
static return_struct range(uint32_t l, uint32_t r, const uint32_t m) noexcept {
  uint32_t i, imin = 0, tmin, min = 0xffffffff;
  for (i = 0; i < m; ++i) {
    if (r + i < m)
      continue;
    tmin = max(a[l + i], a[r - m + i]);
    if (tmin < min) {
      min = tmin;
      imin = i;
    }
  }
  return {l + imin, r - m + imin};
}

[[gnu::hot]] [[gnu::pure]]
static uint32_t accumulator(uint32_t l, uint32_t r, const uint32_t m) noexcept {
  if (l > r)
    return 0;

  if (l + m > r) {
    if (a[l] > a[r])
      return a[l];
    else
      return a[r];
  }

  uint32_t lvalue = a[l];
  return_struct lrange = range(l + 1, r, m);
  uint32_t rvalue = a[r];
  return_struct rrange = range(l, r - 1, m);

  lvalue = lvalue + accumulator(lrange.l, lrange.r, m);
  rvalue = rvalue + accumulator(rrange.l, rrange.r, m);

  return (lvalue > rvalue) ? lvalue : rvalue;
}

[[gnu::hot]] [[gnu::pure]] [[gnu::noinline]]
static bool decider(uint32_t l, uint32_t r, const uint32_t &m) noexcept {
  return (accumulator(l + 1, r, m) > accumulator(l, r - 1, m));
}

[[gnu::noreturn]] [[gnu::noinline]]
static void greedy(uint32_t n, uint32_t m) noexcept {
  uint32_t arr[MAX_M];
  std::memset(arr, 0, sizeof(arr));
  uint32_t r = n - 1, l = 0, i = 0;

  while (l <= r) {
    for (i = 0; i < m; ++i) {
      if (l > r)
        break;

      if (l + m > r) {
        if (a[l] > a[r]) {
          arr[i] += a[l];
          ++l;
        } else {
          arr[i] += a[r];
          --r;
        }
        continue;
      }

      if (decider(l, r, m)) {
        arr[i] += a[l];
        ++l;
      } else {
        arr[i] += a[r];
        --r;
      }
    }
  }

  for (i = 0; i < m; ++i)
    std::cout << arr[i] << ' ';
  exit(0);
}

[[gnu::noreturn]]
int main() noexcept {
  std::cin.tie(NULL);
  std::ios::sync_with_stdio(false);

  uint32_t N, M;
  std::cin >> N >> M;

  for (uint32_t i = 0; i < N; ++i)
    std::cin >> a[i];

  greedy(N, M);
}
