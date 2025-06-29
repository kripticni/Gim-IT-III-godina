#include <iostream>
#include <vector>
using namespace std;

int gridtraveler(int n, int m);
void recursive(int i, int j, const int& n, const int& m, vector<vector<int>>& grid);
int memo(int i, int j, vector<vector<int>>& grid);
inline bool isValidInc(const int& i, const int& j, const int& n, const int& m);
inline bool isValidDec(const int& i, const int& j);
int tabulation(int n, int m);

int gridtraveler(int n, int m){
  if(n == 0 | m == 0) return 0;
  vector<vector<int>> grid(n, vector<int>(m, 0));
  --n; --m;
  //recursive(0, 0, n, m, grid);
  //return grid[n][m];
  grid[0][0] = 1;
  return memo(n,m,grid);
}

void recursive(int i, int j, const int& n, const int& m, vector<vector<int>>& grid){
  if(!isValidInc(i, j, n, m))
    return;
  ++grid[i][j];
  recursive(i+1,j,n,m,grid);
  recursive(i,j+1,n,m,grid);
}

inline bool isValidInc(const int& i, const int& j, const int& n, const int& m){
  if(i > n) return false;
  if(j > m) return false;
  return true;
}

int memo(int i, int j, vector<vector<int>>& grid){
  if(!isValidDec(i,j)) return 0;
  if(grid[i][j]) return grid[i][j];
  grid[i][j] = memo(i-1,j,grid) + memo(i,j-1,grid);
  return grid[i][j];
}

inline bool isValidDec(const int& i, const int& j){
  if(i < 0) return false;
  if(j < 0) return false;
  return true;
}

int tabulation(int n, int m){
  if(n == 0 && m == 0) return 0;
  vector<vector<int>> grid(n, vector<int>(m, 0));
  grid[0][0] = 1;

  int i, j;
  for(i = 0; i < n; ++i)
    for(j = 0; j < m; ++j){
      if(i + 1 < n)
        grid[i+1][j] += grid[i][j];
      if(j + 1 < m)
        grid[i][j+1] += grid[i][j];
    }
  cout << "\ngrid:\n";
  for(i = 0; i < n; ++i){
    for(j = 0; j < m; ++j)
      cout << grid[i][j] << ' ';
    cout << '\n';
  }

  return grid[n-1][m-1];
}

int main(){
  cout << gridtraveler(1, 1) << '\n';
  cout << gridtraveler(2, 3) << '\n';
  cout << gridtraveler(3, 3) << '\n';
  cout << tabulation(1, 1) << '\n';
  cout << tabulation(2, 3) << '\n';
  cout << tabulation(3, 3) << '\n';
}
