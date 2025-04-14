#include <stdio.h>
#include <stdlib.h>

int neusmeren(int g[5][5], int n){
  int i, j;
  for(i = 0; i < n; ++i)
    for(j = i + 1; j < n; ++j){
      if(i == j){
        if(g[i][i] == 1)
          return 0;
      } else {
        if(g[i][j] != g[j][i])
          return 0;
      }
    }

  return 1;
}

int maxStepen(int g[5][5], int n){
    int i,j,br,max=0;
    for(i = 0; i < n; ++i, br=0)
        for(j = 0; i < n; ++i){
            if(g[i][j]==1) ++br;
            if(br>max) max=br;
        }
    return max;
}
int elementStepen(int g[5][5], int k, int n){
    int i, br = 0;
    for(i = 0; i < n; ++i)
        if(g[k][i]==1) ++br;
    return br;
}

int ulazneElementa(int g[5][5], int k, int n){
    int i, br = 0;
    for(i = 0; i < n; ++i)
        if(g[i][k]==1) ++br;
    return br;
}

int povezaniElementi(int g[5][5], int a, int b){
    if(g[a][b] == 1 && g[b][a] == 1){
        printf("Elementi su medjusobno povezani.");
        return 2;
    }
    if(g[a][b] == 1){
        printf("Element A je povezan na element B.");
        return 1;
    }
    if(g[b][a] == 1){
        printf("Element A je povezan na element B.");
        return 1;
    }
    printf("Elementi nisu povezani.");
    return 0;
}

typedef struct{
    char ime[20];
    char prezime[20];
}Osoba;

int maxPrijatelja(int g[5][5], int n){
    int max = 0, imax = 0, br, i, j;
    for(i = 0; i < n; ++i){
        br = 0;
        for(j = 0; j < n; ++j)
            if(g[i][j]==1 && i!=j)
                ++br;
        if(br > max){
            max = br;
            imax = i;
        }
    }
    return imax;
}

void ispisPrijatelja(int g[5][5], Osoba o[5], int i, int n){
    printf("%s %s ima prijatelje:",o[i].ime,o[i].prezime);
    for(int j = 0; j < n; ++j)
        if(g[i][j])
            printf("\t%s %s", o[j].ime, o[j].prezime);
    printf("\n");
}

void ispisSvihPrijatelja(int g[5][5], Osoba o[5], int n){
    for(int i = 0; i < n; ++i)
        ispisPrijatelja(g,o,i,n);
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

  if(neusmeren(matrica1,n))
     printf("Graf je usmeren\n");
  else
   printf("Graf je neusmeren\n");

  if(neusmeren(matrica2,n))
     printf("Graf je usmeren\n");
  else
   printf("Graf je neusmeren\n");
}
