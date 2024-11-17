#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i, j;
int resenja = 1;
int N, M;
bool zastava;

void igra(char tabla[N][M + 1], bool za_promenu[N][M]) {
  zastava = false;

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
      if (tabla[i][j] == 'X' || tabla[i][j] == 'S')
        za_promenu[i][j] = true;

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
      if (za_promenu[i][j] && tabla[i][j] == 'X') {
        za_promenu[i][j] = false;
        if (i != 0)
          if (tabla[i - 1][j] == '.')
            tabla[i - 1][j] = 'X';
        if (j != 0)
          if (tabla[i][j - 1] == '.')
            tabla[i][j - 1] = 'X';
        if (i != N - 1)
          if (tabla[i + 1][j] == '.')
            tabla[i + 1][j] = 'X';
        if (j != M - 1)
          if (tabla[i][j + 1] == '.')
            tabla[i][j + 1] = 'X';
      }

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
      if (za_promenu[i][j]) {
        za_promenu[i][j] = false;
        if (i != 0)
          if (tabla[i - 1][j] == '.') {
            tabla[i - 1][j] = 'S';
            resenja++;
            zastava = true;
          }
        if (j != 0)
          if (tabla[i][j - 1] == '.') {
            tabla[i][j - 1] = 'S';
            resenja++;
            zastava = true;
          }
        if (i != N - 1)
          if (tabla[i + 1][j] == '.') {
            tabla[i + 1][j] = 'S';
            resenja++;
            zastava = true;
          }
        if (j != M - 1)
          if (tabla[i][j + 1] == '.') {
            tabla[i][j + 1] = 'S';
            resenja++;
            zastava = true;
          }
      }
  if (!zastava)
    return;

  igra(tabla, za_promenu);
}

int main() {
  scanf("%i%i", &N, &M);
  char tabla[N][M + 1];
  bool za_promenu[N][M + 1];
  memset(za_promenu, 0, sizeof(za_promenu));

  for (int i = 0; i < N; i++) {
    scanf("%s", tabla[i]);
  }
  // printf("\n");
  // for (int i = 0; i < N; i++) {
  //   printf("%s\n", tabla[i]);
  // }

  igra(tabla, za_promenu);

  // printf("\n");
  // for (int i = 0; i < N; i++) {
  //   printf("%s\n", tabla[i]);
  // }

  printf("%i", resenja);
  return 0;
}
