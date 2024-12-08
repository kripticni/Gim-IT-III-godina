#include <cstdint>
#include <cstring>
#include <iostream>
#include <tuple>

int16_t segmentByAnd(std::tuple<int16_t, int16_t, int> (&segments)[1024],
                     int (&array)[1024], int n) {
  int16_t seg_capacity = 0;
  uint16_t prefix[1024][32];
  std::memset(prefix, 0, sizeof(prefix));

  int i, j, k;
  for (i = 0; i < n; ++i)
    for (j = 0; j < 31; ++j)
      if (array[i] & (1u << j))
        ++prefix[i][j];

  int seg_length, value = 0;
  /*
  for(i = 0; i < n; ++i)
    for(seg_length = i + 1; seg_length < n; ++seg_length)
      for(j = 0; j < 32; ++j){
        if(prefix[seg_length][j] - prefix[i][j] == seg_length - i){
          value |= (1u << j);
        }else{
          segments[seg_capacity++] = {i, seg_length - 1, value};
          break;
        }
      }
  */

  int shift = 0, seg_length_next;
  for (i = 0; i < n; ++i)
    for (seg_length = i + 1; seg_length < n; ++seg_length) {
      if (prefix[seg_length][shift] - prefix[i][shift] == seg_length - i) {
        continue;
      } else {
        for (k = shift + 1; k < 32 && seg_length > i; k++) {
          if (prefix[seg_length][k] - prefix[i][k] == seg_length - i) {
            value |= (1u << j);
          } else {
            segments[seg_capacity++] = {
                i, --seg_length, value}; // should also decrement seg_length
          }
        }
      }
    }
  return seg_capacity;
}
/*
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
*/

/*
int16_t segmentByAnd(std::tuple<int16_t, int16_t, int> (&segments)[1024],
                     int (&array)[1024], int n) {
  // i assume its not bad to bring n closer to the scope of other iterators
  int16_t seg_capacity = 0;
  int i, j, k, seg_length;
  for(i = 0; i<n; i++){
    for(j = 31; j>0; j--){
      if(array[i] & (1 << j)){
        seg_length = i; // R = L
        while(seg_length<n && (array[seg_length+1] & (1 << j))){
          for(k = 0

        }
      }
    }
  }

  return seg_capacity;
}
*/
int main() {
  std::cin.tie(NULL);
  std::ios::sync_with_stdio(false);

  int n;
  std::cin >> n;

  int array[1024]; // assuming there wont be more than 1024, arrays are better
                   // than VLAs and much better than vectors
  for (int i = 0; i < n; ++i)
    std::cin >> array[i];

  std::tuple<int16_t, int16_t, int> segments[1024];
  segmentByAnd(segments, array, n);
}

/*
* #include <array>
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
*/
