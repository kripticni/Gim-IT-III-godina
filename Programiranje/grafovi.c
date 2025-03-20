#include <stdio.h>
#include <stdlib.h>

int jeUsmeren(int g[5][5], int n){
  int i, j;
  for(i = 0; i < n; ++i)
    for(j = i + 1; j < n; ++j){
      if(i == j){
        if(g[i][i] == 1)
          return 1;
      } else {
        if(g[i][j] != g[j][i])
          return 1;
      }
    }

  return 0;
}

int main(){
  const int n = 5;
  int matrica1[5][5] = {
    {0,0,0,1,0},
    {0,0,1,0,1},
    {1,0,0,1,1},
    {1,1,1,0,0},
    {0,0,0,0,0}
  };
  int matrica2[5][5] = {
    {0,1,0,0,1},
    {1,0,0,0,0},
    {0,0,0,1,0},
    {0,0,1,0,0},
    {1,0,0,0,0}
  };

  if(jeUsmeren(matrica1,n))
     printf("Graf je usmeren\n");
  else
   printf("Graf je neusmeren\n");

  if(jeUsmeren(matrica2,n))
     printf("Graf je usmeren\n");
  else
   printf("Graf je neusmeren\n");
}
