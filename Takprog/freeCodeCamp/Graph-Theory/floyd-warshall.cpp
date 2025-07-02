#include <cstdint>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

using namespace std;
constexpr const uint8_t inf = numeric_limits<uint8_t>::max();
constexpr const uint8_t neg_inf =
    numeric_limits<uint8_t>::min(); // not actually neg_inf, use actual neg_inf

void floyd_warshall(unordered_map<uint8_t, unordered_map<uint8_t, uint8_t>> &g);
void delegate_negative_cycles(vector<vector<uint8_t>> &dist,
                              vector<vector<uint8_t>> &next);
vector<uint8_t> reconstruct_path(vector<vector<uint8_t>> &dist,
                                 vector<vector<uint8_t>> &next, uint8_t start,
                                 uint8_t end);

void floyd_warshall(
    unordered_map<uint8_t, unordered_map<uint8_t, uint8_t>> &g) {
  vector<vector<uint8_t>> dp(g.size(), vector<uint8_t>(g.size()));
  vector<vector<uint8_t>> next(g.size(), vector<uint8_t>(g.size(), 0));
  uint8_t i, j, k, n;

  n = g.size();
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j) {
      dp[i][j] = g[i][j]; // just a deep copy
      if (g[i][j] != inf)
        next[i][j] = j;
      // if i can go to j, then next of i is j, if infinity then not
    }

  for (k = 0; k < n; ++k) // start with K to remove a dimension from dp
    for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
        if (dp[i][k] + dp[k][j] <
            dp[i][j]) { // is it better to go i -> k -> j or i -> j
          dp[i][j] = dp[i][k] + dp[k][j]; // if better
          next[i][j] = next[i][k];        // now i goes to k instead of j
        }

  delegate_negative_cycles(dp, next);
}

void delegate_negative_cycles(vector<vector<uint8_t>> &dist,
                              vector<vector<uint8_t>> &next) {
  uint8_t i, j, k, n;

  for (k = 0; k < n; ++k)
    for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = neg_inf; // better to use negative
                                // infinite, this wont work
          next[i][j] = neg_inf; // and here we'd like to put -1 or
                                // an index that doesnt exist
        }
}

vector<uint8_t> reconstruct_path(vector<vector<uint8_t>> &dist,
                                 vector<vector<uint8_t>> &next, uint8_t start,
                                 uint8_t end) {
  vector<uint8_t> path = vector<uint8_t>();
  uint8_t at;
  if (dist[start][end] == inf)
    return path;

  for (at = start; at != end; at = next[at][end]) {
    if (at == neg_inf)
      return vector<uint8_t>();
    path.emplace_back(at);
  }

  if (next[at][end] == neg_inf)
    return vector<uint8_t>();
  path.emplace_back(end);
  return path;
}

int main() noexcept {
  unordered_map<uint8_t, unordered_map<uint8_t, uint8_t>> graph =
      unordered_map<uint8_t, unordered_map<uint8_t, uint8_t>>();

  int16_t input;
  uint8_t n, i, j;
  cin >> n;
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j) {
      cin >> input;
      if (input == -1)
        continue;
      graph[i][j] = input;
    }

  floyd_warshall(graph);
}
