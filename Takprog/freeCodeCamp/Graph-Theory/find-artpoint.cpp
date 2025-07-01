#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

typedef unordered_map<uint16_t, unordered_map<uint16_t, int16_t>> Graph;
constexpr int16_t INF = 30000;
constexpr int16_t NEG_INF = -30000;

vector<uint16_t> find_artpoints(Graph g);
void dfs(Graph g, const int16_t &root, int16_t at, int16_t prev, uint16_t id,
         uint16_t outEdges, vector<bool> &artpoints, vector<uint16_t> &ids,
         vector<uint16_t> &low_link, vector<bool> &visited);

vector<bool> find_artpoints(Graph g) {
  vector<uint16_t> ids = vector<uint16_t>(g.size(), 0);
  vector<uint16_t> low_link = vector<uint16_t>(g.size(), 0);
  vector<bool> visited = vector<bool>(g.size(), false);
  uint16_t n = g.size();
  uint16_t id = 0;
  uint16_t i = 0;
  uint16_t outEdges; // stores number of outgoing edges for node
  // an articulation point is where there is a cycle present
  // and more than 1 outgoing edge, a cycle is present
  // when the low_link is the same as the id

  vector<bool> artpoints = vector<bool>(n);
  for (i = 0; i < n; ++i)
    if (!visited[i]) {
      outEdges = 0;
      dfs(g, i, i, -1, id, outEdges, artpoints, ids, low_link, visited);
      artpoints[i] = (outEdges > 1);
    }
  return artpoints;
}

void dfs(Graph g, const int16_t &root, int16_t at, int16_t prev, uint16_t id,
         uint16_t outEdges, vector<bool> &artpoints, vector<uint16_t> &ids,
         vector<uint16_t> &low_link, vector<bool> &visited) {
  if (prev == root)
    ++outEdges;
  visited[at] = true;
  id = id + 1;
  low_link[at] = ids[at] = id;

  for (auto to : g[at]) {
    if (to.first == prev)
      continue;
    if (!visited[to.first]) {
      dfs(g, root, to.first, at, outEdges, id, artpoints, ids, low_link,
          visited);
      low_link[at] = min(low_link[at], low_link[to.first]);
      // found by bridge
      if (ids[at] < low_link[to.first])
        artpoints[at] = true;
      // found by cycle
      if (ids[at] == low_link[to.first])
        artpoints[at] = true;
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

  auto artpoints = find_artpoints(graph);
  bool parity = true;
  for (auto a : artpoints)
    std::cout << a << '\n';
}
