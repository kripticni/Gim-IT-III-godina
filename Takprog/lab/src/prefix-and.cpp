#include <array>
#include <bitset>
#include <iostream>
#include <stdint.h>
#include <vector>

std::vector<std::array<int, 32>> prefixAnd(std::vector<int> array) {
  std::vector<std::array<int, 32>> prefix(array.size());

  int i, j, n;
  for (i = 0, n = array.size() - 1; i < n; ++i) {
    for (j = 0; j < 32; ++j)
      if (array[i] & (1u << j))
        ++prefix[i][j];
    prefix[i + 1] = prefix[i];
  }

  for (j = 0; j < 32; ++j)
    if (array[i] & (1u << j))
      ++prefix[i][j];

  return prefix;
}

int rangeAnd(int L, int R, std::vector<std::array<int, 32>> array) {
  int ret = 0;

  for (int i = 0; i < 32; i++)
    if (array[R][i] - array[L][i] == R - L)
      ret |= (1u << i);

  return ret;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::vector<int> B(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> B[i];
    std::cout << std::bitset<32>(B[i]) << '\n';
  }

  auto prefix = prefixAnd(B);
  std::cout << rangeAnd(1, 3, prefix);
}
