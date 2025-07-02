#include <cstdint>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

typedef unordered_map<uint16_t, unordered_map<uint16_t, int16_t>> Graph;
constexpr int16_t INF = 30000;
constexpr int16_t NEG_INF = -30000;
constexpr int16_t unvisited = -1;

vector<int16_t> ids;
vector<int16_t> low_link;
stack<uint16_t> tstack;
vector<bool> onStack;
int16_t id = 0;
int16_t sccCount = 0;

// using tarjan's algorithm with the stack
vector<int16_t> find_sccs(Graph g);
void dfs(Graph &g, uint16_t at);

vector<int16_t> find_sccs(Graph g) {
  uint16_t n = g.size(), i;
  ids = vector<int16_t>(n, unvisited);
  low_link = vector<int16_t>(n, 0);
  onStack = vector<bool>(n, false);
  tstack = stack<uint16_t>();

  for (i = 0; i < n; ++i)
    if (ids[i] == unvisited)
      dfs(g, i);
  return low_link;
}

void dfs(Graph &g, uint16_t at) {
  tstack.push(at);
  onStack[at] = true;
  ids[at] = low_link[at] = id++;

  for (auto to : g[at]) {
    if (ids[to.first] == unvisited)
      dfs(g, to.first);
    if (onStack[to.first])
      low_link[at] = min(low_link[at], low_link[to.first]);
  }

  if (ids[at] == low_link[at]) {
    uint16_t node = tstack.top();
    tstack.pop();
    while (true) { // goes backwards through the nodes and checks them
      onStack[node] = false;
      low_link[node] = ids[at];
      if (node == at)
        break;
      node = tstack.top();
      tstack.pop();
    }
    ++sccCount;
  }
}

int main() noexcept {
  Graph graph;
  graph[0][1] = 1;
  // graph[1][0] = 1;
  graph[1][2] = 1;
  // graph[2][1] = 1;
  graph[2][0] = 1;
  // graph[0][2] = 1;
  graph[2][5] = 1;
  // graph[5][2] = 1;
  graph[2][3] = 1;
  // graph[3][2] = 1;
  graph[5][6] = 1;
  // graph[6][5] = 1;
  graph[3][4] = 1;
  // graph[4][3] = 1;
  graph[6][7] = 1;
  // graph[7][6] = 1;
  graph[7][8] = 1;
  // graph[8][7] = 1;
  graph[5][8] = 1;
  // graph[8][5] = 1;

  for (auto s : find_sccs(graph))
    cout << s << '\n';
}
