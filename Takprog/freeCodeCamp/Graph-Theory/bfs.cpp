#include <array>
#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
constexpr const uint8_t n = 5;
vector<vector<bool>> g1;
vector<vector<bool>> g2;

void bfs(vector<vector<bool>> g, uint8_t node) {
  queue<uint8_t> q = queue<uint8_t>();
  array<bool, n> visited{};
  uint8_t i;
  q.push(node);
  visited[node] = true;
  while (!q.empty()) {
    node = q.front();
    q.pop();
    for (i = 0; i < n; ++i) {
      if (visited[i] || !g[node][i])
        continue;
      cout << (uint16_t)node << "->" << (uint16_t)i << ' ';
      q.push(i);
      visited[i] = true;
    }
  }
}

int main() noexcept {
  g1 = {{0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0}};
  g2 = {{0, 0, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 1},
        {1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0}};

  bfs(g1, 0);
  cout << '\n';
  bfs(g2, 0);
}
