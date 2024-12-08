#include <bitset>
#include <iostream>
#include <tuple>

constexpr int16_t MAX = 1024;

void segmentAnd(std::bitset<32> (&bits)[MAX],
                std::tuple<int16_t, int16_t, int32_t> (&segments)[MAX / 2 + 1],
                int32_t n) {
  std::pair<int16_t, int16_t>
      bitSegments[MAX / 2 + 1]
                 [32]; // nice memory save, since at max every 2nd bit can be
                       // set and that would create half the max size
  int16_t segmentsMax[32] = {0};

  int16_t i, j, k;
  for (k = 0; k < 32; ++k) {
    i = 0;
    while (i < n) {
      while (i < n && !bits[i][k])
        ++i;
      if (i >= n)
        break;
      j = i;

      while (j < n && bits[j][k])
        ++j;
      bitSegments[segmentsMax[k]++][k] = {i, j - 1};

      i = j;
    }
  }
  /*
  for (k = 0; k < 32; ++k) {
    for (i = 0; i < n; ++i) {
      if (!bits[i][k])
        continue;

      for (j = i + 1; j < n; ++j) {
        if (!bits[j][k]) {
          bitSegments[segmentsMax++][k] = {
              i, j - 1}; // no need for bounds checking since it can never be
                         // greater than MAX/2+1 which is allocated
          i = j;
        }
      }
    }
  }
  */

  /*
  j = 0;
  for (j = 0; j < 32; ++j) {
    if (segmentsMax[j])
      std::cout << segmentsMax[j] << '\n';
    for (i = 0; i < segmentsMax[j]; ++i)
      std::cout << j << ':' << " ( " << bitSegments[i][j].first << " , "
                << bitSegments[i][j].second << " )\n";
  }
  */

  int16_t segSize = 0;
  j = 0, k = 0;
  while (j < segmentsMax[0] && k < segmentsMax[0 + 1]) {
  }
  for (i = 2; i < 31; ++i, j = 0,
      k = 0) { // because we'll be using i + 1, its now less than 32
  }
}

int main() {
  std::cin.tie(NULL);
  std::ios::sync_with_stdio(false);

  int32_t n;
  std::cin >> n;

  std::bitset<32> bitset[MAX];
  for (int i = 0, temp; i < n; ++i) {
    std::cin >> temp;
    bitset[i] = std::bitset<32>(temp);
  }

  std::tuple<int16_t, int16_t, int32_t> segments[MAX / 2 + 1];
  segmentAnd(bitset, segments, n);
}
