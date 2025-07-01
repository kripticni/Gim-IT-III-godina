#include <algorithm>
#include <array>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;
constexpr const uint8_t n = 4;
vector<vector<bool>> g;
vector<uint8_t> comp;
array<bool, n> visited{};
uint8_t id_max = 0;

void dfs(uint8_t at);

[[gnu::always_inline]]
inline pair<uint8_t, vector<uint8_t>> findComponents() {
  for (uint8_t i = 0; i < n; ++i) {
    if (visited[i])
      continue;
    dfs(i);
    ++id_max;
  }
  return pair<uint8_t, vector<uint8_t>>(id_max, comp);
}

void dfs(uint8_t at) {
  visited[at] = true;
  comp[at] = id_max;
  for (uint8_t i = 0; i < n; ++i) {
    if (visited[i])
      continue;
    if (!g[at][i])
      continue;
    dfs(i);
  }
}

int main() noexcept {
  g = {{0, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}};
  comp = vector<uint8_t>(n);

  findComponents();
  for (uint8_t i = 0; i < n; ++i)
    std::cout << (uint16_t)comp[i] << ' ';
}
