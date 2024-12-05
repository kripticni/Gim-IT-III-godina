#include <array>
#include <bitset>
#include <iostream>
#include <math.h>
#include <queue>
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
  int ret = 0, i;

  for (i = 0; i < 32; ++i)
    if (array[R][i] - array[L][i] == R - L)
      ret |= (1u << i);

  return ret;
}

std::vector<std::pair<int, int>>
segmentsAnd(std::vector<std::array<int, 32>> array) {
  std::vector<std::pair<int, int>> segments(std::sqrt(array.size()));

  int i, j, n = array.size(), seg_length, count_true;
  for (i = 0, seg_length = 1; i < n; ++i) {
  loop:
    if (seg_length > n)
      break;
    for (j = 0, count_true = 0; j < 32; ++j) {
      if (array[seg_length][j] - array[i][j] == seg_length - i) {
        ++count_true;
      } else {
        segments.emplace_back(i, seg_length);
        i = seg_length; // ++i se svakako desi na kraj
        seg_length = seg_length + 2;
        break;
      }
    }
    if (count_true == 32) {
      ++seg_length;
      goto loop;
    }
  }
  return segments;
} // this logic is not what i was looking for but i wont scrap it

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
  auto segments = segmentsAnd(prefix);
  for (auto &s : segments)
    std::cout << s.first << ' ' << s.second << '\n';
}
