#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;
constexpr const uint8_t n = 7;
vector<vector<uint8_t>> g;

vector<uint8_t> top_sort(vector<vector<uint8_t>> graph);
void dfs(const vector<vector<uint8_t>> &graph, uint8_t at,
         vector<uint8_t> &sort, vector<bool> &visited);

vector<uint8_t> top_sort(vector<vector<uint8_t>> graph) {
  vector<uint8_t> sort = vector<uint8_t>();
  vector<bool> visited = vector<bool>(n);
  uint8_t i;

  sort.reserve(n);

  for (i = 0; i < n; ++i) {
    if (visited[i])
      continue;
    dfs(graph, i, sort, visited);
  }

  reverse(sort.begin(), sort.end());
  return sort;
}

void dfs(const vector<vector<uint8_t>> &graph, uint8_t at,
         vector<uint8_t> &sort, vector<bool> &visited) {
  visited[at] = true;
  for (uint8_t node : graph[at]) {
    if (visited[node])
      continue;
    dfs(graph, node, sort, visited);
  }
  sort.emplace_back(at);
}

int main() {
  vector<vector<uint8_t>> g = {{1, 2}, {3, 4}, {3}, {4}, {5}, {6}, {}};
  vector<uint8_t> sorted_graph = top_sort(g);
  for (uint8_t node : sorted_graph)
    cout << (uint16_t)node << " -> ";
}
