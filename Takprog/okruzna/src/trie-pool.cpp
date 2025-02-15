#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

constexpr const uint32_t MAX = uint32_t(100000);
constexpr const uint32_t NODES = MAX * 31;

uint32_t root[MAX];
uint32_t trie[NODES+5][2];
uint32_t stack[NODES+5], stack_begin, stack_end;

//ret = index of allocated node
static inline uint32_t allocNode(){
  uint32_t ret = stack[stack_begin];
  stack_begin = (stack_begin + 1) % NODES; //ensuring circularity
  return ret;
}

//arg = node to free
static inline void freeNode(uint32_t node){
  stack_end = (stack_end + 1) % NODES;
  stack[stack_end] = node; // puts the id of the same node at the end
}

static void trieInsert(uint32_t& node, uint32_t val, int8_t bit){
  if(!node)
    node = allocNode();

  if(bit < 0)
    return;

  uint8_t left_or_right = (val >> bit & 1);
  trieInsert(trie[node][left_or_right], val, bit - 1);
}

static void trieErase(uint32_t& node){
  if(trie[node][0] > 0)
    trieErase(trie[node][0]);
  if(trie[node][1] > 0)
    trieErase(trie[node][1]);

  freeNode(node);
  node = 0;
}

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::vector<uint32_t> arr, sol;
  uint32_t n, i;
  uint8_t t, ti;

  std::cin >> n;
  t = n; // da lepo unesemo uint8_t
  std::cin >> n;

  for(ti = 0; ti < t; ++ti){
    arr = std::vector<uint32_t>(n);
    sol = std::vector<uint32_t>(n);
    stack_begin = 0;
    stack_end = NODES-1;

    for(i = 0; i < n; ++i)
      std::cin >> arr[i];


    std::memset(trie, 0, sizeof(trie));
    std::memset(stack, 0, sizeof(stack));
    std::memset(root,  0, sizeof(root));
  }
}
