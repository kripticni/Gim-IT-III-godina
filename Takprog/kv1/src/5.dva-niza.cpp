#include <bits/stdc++.h>

const int MAX = int(2e5);   // maximum input size
const int NODES = MAX * 31; // allocated nodes for the trie
//
int root[MAX]; // array of root nodes, one for each segment in the array
               // each root points to a trie structure for storing prefix XOR
               // values
int trie[NODES + 5]
        [2]; // the trie structure, 0 and 1 representing left and right

int stack[NODES + 5], stack_begin, stack_end; // stack of reusable node ids
// more of a pool of preallocated stack nodes to avoid mallocing

std::vector<int> values[MAX];

void max(int64_t &a, int64_t &&b) {
  if (a > b)
    return;
  else
    a = b;
}

/*int64_t max(int64_t a, int64_t b) {
  if (a > b)
    return a;
  else
    return b;
}*/

// algorithm for finding the biggest xor from a trie
int32_t maxor(int node, int bit,
              int value) { /// node is current node for insert/query/clear
  if (bit < 0)
    return 0;

  int current_bit = (value >> bit & 1);

  if (trie[node][current_bit ^ 1] >
      0) // ^ is like a not but only for the first bit, and we must use an int
         // for indexing
    return maxor(trie[node][current_bit ^ 1], bit - 1, value) + (1 << bit);
  else
    return maxor(trie[node][current_bit], bit - 1, value);
}

int allocNode() {
  int ret_val = stack[stack_begin];
  stack_begin = (stack_begin + 1) %
                NODES; // if you allocate more nodes than possible, it will wrap
                       // around, and overwrite the array (bad)
  return ret_val;
}

void insertXor(int &node, int bit, int val) {
  if (!node)
    node = allocNode();

  if (bit < 0)
    return;

  int current_bit = (val >> bit & 1);
  insertXor(trie[node][current_bit], bit - 1, val);
}

void freeNode(int node) { // if there is more frees than allocs, this corrupts
                          // data but that shouldnt happen with this program
  stack_end = (stack_end + 1) % NODES;
  stack[stack_end] = node;
}

void clearState(int &node) {
  if (trie[node][0] > 0) // if left has a state, clear it
    clearState(trie[node][0]);

  if (trie[node][1] > 0) // if right has a state, clear it
    clearState(trie[node][1]);

  freeNode(node); // frees itself
  node = 0;       // return 0 with rvo
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);

  stack_begin = 0;
  stack_end = NODES - 1; // everything is reusable

  int n;
  int64_t result = 0;
  std::cin >> n;

  std::vector<int> a(n);
  std::vector<int> b(n);
  std::vector<int> pref(n);                  // prefix sum/xor
  std::vector<std::pair<int, int>> segments; // first is the bitwise and result
                                             // of the elements in the segment
  // second is the index where the given segment starts
  //
  int i;

  for (i = 0; i < NODES; i++)
    stack[i] = i + 1;

  for (i = 0; i < n; ++i)
    std::cin >> a[i];

  std::cin >> b[0];
  pref[0] = a[0];
  for (i = 1; i < n; ++i) {
    std::cin >> b[i];
    pref[i] = pref[i - 1] ^ a[i];
  }

  for (i = 0; i < n; ++i) {
    result = ((long long)a[i] * (long long)b[i] > result)
                 ? (long long)a[i] * (long long)b[i]
                 : result;

    for (auto &p : segments)
      p.first &=
          b[i]; // this does nothing when vector length is 0, aka when i = 0

    for (auto &p : segments)
      max(result,
          int64_t(maxor(root[p.second], 31, pref[i]) * int64_t(p.first)));

    segments.emplace_back(b[i], i);
    insertXor(root[i], 31, i == 0 ? 0 : pref[i - 1]);
    values[i].push_back(i == 0 ? 0 : pref[i - 1]);
    {
      // this merges consecutive subarrays with the same bitwise and result (aka
      // segments.first)
      std::vector<std::pair<int, int>> new_segments;
      int x, y, t;
      for (x = 0; x < int(segments.size()); x++) {
        y = x;
        while (y + 1 < int(segments.size()) &&
               segments[y + 1].first == segments[x].first)
          y += 1; // this finds the first x and last y with the same bitwise and
                  // values for the subarray

        int pos = segments[x].second; // the index of starting
        for (t = x + 1; t <= y; t++) {
          clearState(root[segments[t].second]); // frees nodes from x + 1 to y
          for (int v :
               values[segments[t].second]) { // take xor, at index of and-value,
                                             // repeats only once
            insertXor(root[pos], 31, v);     // inserts at starting x
            // the merging happens at the line above
            values[pos].push_back(v);
          }
        } // now all of these have merged
        new_segments.push_back(segments[x]);
        x = y; // skip ahead to next segment without the same and values
      }
      swap(segments, new_segments); // replace old segs, with the merged segs
    }
  }
  std::cout << result;
}
