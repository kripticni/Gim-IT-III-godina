#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

typedef unordered_map<uint16_t, unordered_map<uint16_t, int16_t>> Graph;
constexpr int16_t INF = 30000;
constexpr int16_t NEG_INF = -30000;

vector<uint16_t> find_bridges(Graph g);
void dfs(Graph g, int16_t at, int16_t prev, uint16_t id,
         vector<uint16_t> &bridges, vector<uint16_t> &ids,
         vector<uint16_t> &low_link, vector<bool> &visited);

vector<uint16_t> find_bridges(Graph g) {
  vector<uint16_t> ids = vector<uint16_t>(g.size(), 0);
  vector<uint16_t> low_link = vector<uint16_t>(g.size(), 0);
  vector<bool> visited = vector<bool>(g.size(), false);
  uint16_t n = g.size();
  uint16_t id = 0;
  uint16_t i = 0;

  vector<uint16_t> bridges = vector<uint16_t>();
  for (i = 0; i < n; ++i)
    if (!visited[i])
      dfs(g, i, -1, id, bridges, ids, low_link, visited);
  return bridges;
}

void dfs(Graph g, int16_t at, int16_t prev, uint16_t id,
         vector<uint16_t> &bridges, vector<uint16_t> &ids,
         vector<uint16_t> &low_link, vector<bool> &visited) {
  visited[at] = true;
  id = id + 1;
  low_link[at] = ids[at] = id;

  for (auto to : g[at]) {
    if (to.first == prev)
      continue;
    if (!visited[to.first]) {
      dfs(g, to.first, at, id, bridges, ids, low_link, visited);
      low_link[at] = min(low_link[at], low_link[to.first]);
      if (ids[at] < low_link[to.first]) {
        bridges.emplace_back(at);
        bridges.emplace_back(to.first);
      }
    } else
      low_link[at] = min(low_link[at], ids[to.first]);
  }
}

int main() noexcept {
  Graph graph;
  graph[0][1] = 1;
  graph[1][0] = 1;
  graph[1][2] = 1;
  graph[2][1] = 1;
  graph[2][0] = 1;
  graph[0][2] = 1;
  graph[2][5] = 1;
  graph[5][2] = 1;
  graph[2][3] = 1;
  graph[3][2] = 1;
  graph[5][6] = 1;
  graph[6][5] = 1;
  graph[3][4] = 1;
  graph[4][3] = 1;
  graph[6][7] = 1;
  graph[7][6] = 1;
  graph[7][8] = 1;
  graph[8][7] = 1;
  graph[5][8] = 1;
  graph[8][5] = 1;

  auto bridges = find_bridges(graph);
  bool parity = true;
  for (auto b : bridges) {
    if (parity)
      std::cout << b << " -> ";
    else
      std::cout << b << '\n';
    parity = !parity;
  }
}
