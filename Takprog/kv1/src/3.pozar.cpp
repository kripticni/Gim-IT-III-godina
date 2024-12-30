#include <bits/stdc++.h>
using namespace std;

char tab[1003][1003];
bool vis[1003][1003];
int vdist[1003][1003];
int sdist[1003][1003];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    cin >> tab[i];

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      vdist[i][j] = 1e9, sdist[i][j] = vdist[i][j];

  int sx, sy;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (tab[i][j] == 'S') {
        sx = i, sy = j;
        break;
      }

  queue<pair<pair<int, int>, int>> bfs;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (tab[i][j] == 'X')
        bfs.push({{i, j}, 0});
  while (!bfs.empty()) {
    int i = bfs.front().first.first;
    int j = bfs.front().first.second;
    int d = bfs.front().second;
    bfs.pop();
    if (i < 0 || i >= n || j < 0 || j >= m)
      continue;
    if (tab[i][j] == '*' || vis[i][j])
      continue;
    vis[i][j] = true;
    vdist[i][j] = d;
    bfs.push({{i + 1, j}, d + 1});
    bfs.push({{i - 1, j}, d + 1});
    bfs.push({{i, j - 1}, d + 1});
    bfs.push({{i, j + 1}, d + 1});
  }

  while (!bfs.empty())
    bfs.pop();

  memset(vis, 0, sizeof(vis));

  bfs.push({{sx, sy}, 0});
  while (!bfs.empty()) {
    int i = bfs.front().first.first;
    int j = bfs.front().first.second;
    int d = bfs.front().second;
    bfs.pop();
    if (i < 0 || i >= n || j < 0 || j >= m)
      continue;
    if (tab[i][j] == '*' || vis[i][j])
      continue;
    vis[i][j] = true;
    sdist[i][j] = d;
    bfs.push({{i + 1, j}, d + 1});
    bfs.push({{i - 1, j}, d + 1});
    bfs.push({{i, j - 1}, d + 1});
    bfs.push({{i, j + 1}, d + 1});
  }

  int ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (sdist[i][j] < vdist[i][j])
        ans++;

  cout << ans << "\n";
}
