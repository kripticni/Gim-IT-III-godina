#include <cstdint>
#include <cstring>
#include <iostream>

constexpr const int MAX_N = 10000;
constexpr const int MAX_M = 10000;

uint32_t a[MAX_N];

/* optimal-naive
[[gnu::noreturn]] [[gnu::hot]] [[gnu::noinline]]
static void greedy(uint32_t *left, uint32_t n, uint32_t m) noexcept {
  uint32_t arr[MAX_M] = {0};
  std::memset(arr, 0, sizeof(arr));
  uint32_t i;

  uint32_t *right = a + n - 1;
  while (left <= right) {
    for (i = 0; i < m; ++i) {
      if (left > right)
        break;
      if (*left > *right) {
        //std::cout << *left << '\n';
        arr[i] += *left;
        ++left;
      } else {
        //std::cout << *right << '\n';
        arr[i] += *right;
        --right;
      }
    }
  }

  for (i = 0; i < m; ++i)
    std::cout << arr[i] << ' ';

  exit(0);
}
*/
[[gnu::always_inline]]
static uint32_t max(uint32_t a, uint32_t b) {
  return (a > b) ? a : b;
}

[[gnu::always_inline]]
static uint32_t min(uint32_t a, uint32_t b) {
  return (a < b) ? a : b;
}

[[gnu::hot]] [[gnu::noinline]]
static uint32_t decide(uint32_t *left, uint32_t *right, uint32_t m) noexcept {
  if (left > right)
    return 0;

  bool flag = 0;
  uint32_t min = 0xffffffff;
  uint32_t tmin = 0xffffffff, imin = 0, i;
  for (i = 0; i < m; ++i) {
    if (left + i < right - m - i) {
      tmin = max(*(left + i), *(right - m + i));
      flag = 1;
    } else
      break;
    if (tmin < min) {
      min = tmin;
      imin = i;
    }
  }

  if (flag) {
    uint32_t lval =
        decide(left + imin + 1, right - m + imin, m) + *(left + imin + 1);
    uint32_t rval =
        decide(left + imin, right - m + imin - 1, m) + *(right - m + imin - 1);

    return (lval > rval) ? lval : rval;
  } else
    return 0;
}

static uint32_t decider(uint32_t *left, uint32_t *right, uint32_t m) {
  if (left > right)
    return 0;

  if (decide(left + 1, right, m) + *(left + 1) >
      decide(left, right - 1, m) + *(right - 1))
    return 1;
  else
    return 2;
}

[[gnu::noreturn]] [[gnu::noinline]]
static void greedy(uint32_t *left, uint32_t n, uint32_t m) noexcept {
  uint32_t arr[MAX_M];
  std::memset(arr, 0, sizeof(arr));
  uint32_t *right = a + n - 1;
  uint32_t i;

  while (left < right) {
    for (i = 0; i < m; ++i) {
      switch (decider(left, right, m - 1)) {
      case 0:
        goto ispis;
      case 1:
        arr[i] += *left;
        ++left;
        break;
      case 2:
        arr[i] += *right;
        --right;
        break;
      }
    }
  }

ispis:
  for (i = 0; i < m; ++i)
    std::cout << arr[i] << ' ';
  exit(0);
}

[[gnu::noreturn]]
int main() noexcept {
  std::cin.tie(NULL);
  std::ios::sync_with_stdio(false);

  uint32_t M, N;
  std::cin >> N >> M;

  for (uint32_t i = 0; i < N; ++i)
    std::cin >> a[i];

  greedy(a, N, M);
}
