#include <bitset>
#include <iostream>
#include <tuple>

constexpr int16_t MAX = 16000;

#define left first
#define right second

void init_remainder(
    std::tuple<int16_t, int16_t, int32_t> (&segments)[MAX / 2 + 1],
    int32_t &size, std::pair<int16_t, int16_t> (&pair)[MAX / 2 + 1][32],
    int16_t &i, int16_t &j, int16_t &n1, int16_t &n2) {
  // FIX: MAYBE NEED TO INCREMENT I OR J BEFORE INSERTING
  if (i < n1) {
    do {
      segments[size++] = {pair[i][0].left, pair[i][0].right, 1};
      ++i;
    } while (i < n1);
    return;
  }
  while (j < n2) {
    segments[size++] = {pair[j][1].left, pair[j][1].right, 2};
    ++j;
  }
}

void init_increment(std::pair<int16_t, int16_t> (&pair)[MAX / 2 + 1][32],
                    int16_t &i, int16_t &j, int16_t &n1, int16_t &n2) {
  if (n1 < 1) {
    i = n1;
    return;
  }
  if (n2 < 1) {
    j = n2;
    return;
  }
  if (i + 1 < n1) {
    if (j + 1 < n2) {
      if (pair[i + 1][0].left < pair[j + 1][1].left)
        ++i;
      else
        ++j;
      return;
    } else {
      ++i;
      return;
    }
  } else {
    if (j + 1 < n2) {
      ++j;
      return;
    }
  }
}

void init_triCase(
    std::tuple<int16_t, int16_t, int32_t> (&segments)[MAX / 2 + 1],
    std::pair<int16_t, int16_t> &A, std::pair<int16_t, int16_t> &B,
    int32_t &size) {
  if (A.left < B.left) {
    // L1-L2
    if (A.right < B.right) {                    // L1 - L2 - R1 - R2
      segments[size++] = {A.left, B.left, 1};   // L1 - L2
      segments[size++] = {B.left, A.right, 3};  // L2 - R1
      segments[size++] = {A.right, B.right, 2}; // R1 - R2
    } else {                                    // L1 - L2 - R2 - R1
      segments[size++] = {B.left, B.right, 3};  // L2 - R2
      segments[size++] = {A.left, A.right, 1};  // L1 - L2 - R2 - R1
    }
  } else {
    // L2 - L1
    if (A.right < B.right) {                    // L2 - L1 - R1 - R2
      segments[size++] = {A.left, B.right, 2};  // L2 - R2
      segments[size++] = {A.left, A.right, 3};  // L1 - R1
    } else {                                    // L2 - L1 - R2 - R1
      segments[size++] = {B.left, A.left, 2};   // L2 - L1
      segments[size++] = {A.left, B.right, 3};  // L1 - R2
      segments[size++] = {B.right, A.right, 1}; // R2 - R1
    }
  }
}

bool init_equal(std::tuple<int16_t, int16_t, int32_t> (&segments)[MAX / 2 + 1],
                std::pair<int16_t, int16_t> &A, std::pair<int16_t, int16_t> &B,
                int32_t &size) {
  if (A.left == B.left) {
    if (A.right == B.right) {
      segments[size++] = {A.left, A.right, 3};
      return true;
    }
    if (A.right < B.right) {
      segments[size++] = {A.left, A.right, 3};
      segments[size++] = {A.right + 1, B.right, 1};
      return true;
    } else {
      segments[size++] = {B.left, B.right, 3};
      segments[size++] = {B.right + 1, A.right, 2};
      return true;
    }
  } else {
    if (A.right == B.right) {
      if (A.left < B.left) {
        segments[size++] = {A.left, B.left - 1, 1};
        segments[size++] = {B.left, B.right, 3};
        return true;
      } else {
        segments[size++] = {B.left, A.left - 1, 1};
        segments[size++] = {A.left, A.right, 3};
        return true;
      }
    }
  }
  return false;
}
bool init_leftOf(std::tuple<int16_t, int16_t, int32_t> (&segments)[MAX / 2 + 1],
                 std::pair<int16_t, int16_t> &A, std::pair<int16_t, int16_t> &B,
                 int16_t &i, int16_t &j, int32_t &size) {
  // FIX maybe run this in a while loop before
  if (A.right < B.left) {
    // this needs to push only if one pair was never used
    // segments[size++] = {A.left, A.right, 1};
    ++i;
    return true;
  }
  if (B.right < A.left) {
    ++j;
    // segments[size++] = {B.left, B.right, 2};
    return true;
  }
  return false;
}

int32_t
mergeSegments(std::pair<int16_t, int16_t> (&pair)[MAX / 2 + 1][32],
              std::tuple<int16_t, int16_t, int32_t> (&segments)[MAX / 2 + 1],
              int16_t (&n)[32]) {
  int32_t size = 0;
  int16_t i = 0, j = 0;

  while (i < n[0] && j < n[1]) { // initing the merged segments
    if (init_leftOf(segments, pair[i][0], pair[j][1], i, j, size))
      continue;
    if (init_equal(segments, pair[i][0], pair[j][1], size))
      goto decide;
    init_triCase(segments, pair[i][0], pair[j][1], size);

  decide:
    init_increment(pair, i, j, n[0], n[1]);
  }
  init_remainder(segments, size, pair, i, j, n[0], n[1]);

  for (int z = 0; z < size; z++)
    std::cout << z << ": ( " << std::get<0>(segments[z]) << " , "
              << std::get<1>(segments[z]) << " ): " << std::get<2>(segments[z])
              << '\n';

  return size;
}
#undef first
#undef second

int32_t
retrieveSegments(std::bitset<32> (&bits)[MAX],
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

  return mergeSegments(bitSegments, segments, segmentsMax);
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
  retrieveSegments(bitset, segments, n);
}
