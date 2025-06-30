#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
constexpr const uint8_t n = 5;
vector<vector<bool>> g;

vector<uint8_t> bfs_shortest_path(vector<vector<bool>> g, uint8_t start,
                                  uint8_t end);
vector<uint8_t> reconstruct_path(array<uint8_t, n> r, uint8_t s, uint8_t e);

vector<uint8_t> bfs_shortest_path(vector<vector<bool>> g, uint8_t start,
                                  uint8_t end) {
  queue<uint8_t> q = queue<uint8_t>();
  array<bool, n> visited{};
  array<uint8_t, n> parent{};
  uint8_t node, i;

  visited[start] = true;
  q.push(start);

  while (!q.empty()) {
    node = q.front();
    q.pop();
    for (i = 0; i < n; ++i) {
      if (visited[i] || !g[node][i])
        continue;
      q.push(i);
      parent[i] = node;
      visited[i] = true;
      if (i == end)
        return reconstruct_path(parent, start, end);
    }
  }

  return {};
}

vector<uint8_t> reconstruct_path(array<uint8_t, n> r, uint8_t s, uint8_t e) {
  vector<uint8_t> path = vector<uint8_t>();

  uint8_t node = e;
  do {
    path.emplace_back(node);
    node = r[node];
  } while (node != s);
  path.emplace_back(s);

  reverse(path.begin(), path.end());
  return path;
}

int main() noexcept {
  g = {{0, 0, 0, 1, 0},
       {0, 0, 1, 0, 1},
       {1, 0, 0, 1, 1},
       {1, 1, 1, 0, 0},
       {0, 0, 0, 0, 0}};
  vector<uint8_t> path = bfs_shortest_path(g, 0, 4);
  for (uint8_t node : path)
    cout << (uint16_t)node << " -> ";
}
