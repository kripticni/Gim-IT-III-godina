#include <stdio.h>
#include <stdlib.h>

int jeNeusmeren(int n, int g[n][n]) {
  int i, j;
  for (i = 0; i < n; ++i)
    for (j = i + 1; j < n; ++j)
      if (g[i][i] == 1) // ako ciklican
        return 0;
      else if (g[i][j] != g[j][i])
        return 0;
  // ako je jedna grana usmerena
  return 1;
}

int jeUsmeren(int n, int g[n][n]) { return (jeNeusmeren(n, g)) ? 0 : 1; }

int maxStepen(int n, int g[n][n]) {
  int i, j, tr = 0, max = 0;
  for (i = 0; i < n; ++i, tr = 0) {
    for (j = 0; j < n; ++j)
      if (g[i][j])
        ++tr;
    max = (tr > max) ? tr : max;
  }
  return max;
}

int minStepen(int n, int g[n][n]) {
  int i, j, tr = 0, max = 0;
  for (i = 0; i < n; ++i, tr = 0) {
    for (j = 0; j < n; ++j)
      if (g[i][j])
        ++tr;
    max = (tr < max) ? tr : max;
  }
  return max;
}

// lista
typedef struct cvor {
  int vrednost;
  struct cvor *sledeci; // adresa sledeceg cvora
} Cvor;

// niz listi susedstva
typedef struct graf {
  int n; // broj cvorova
  Cvor **g;
  // niz koji sadrzi cvorove koji su koreni, odnosno niz raznih lista
  // struct Cvor* g[]; //je bolji opis
  //
  // lista izgleda ovako
  // (Cvor[0].vrednost nek bude 1, znaci da 0 ima granu sa 1)
  // (Cvor[0].sledeci je sledeca grana sa cvorom 0)
} Graf;

Cvor *noviCvor(int vrednost) {
  Cvor *novi = (Cvor *)malloc(sizeof(Cvor));
  novi->vrednost = vrednost;
  novi->sledeci = NULL;
  return novi;
}

Graf *noviGraf(int n) {
  Graf *graf = (Graf *)malloc(sizeof(Graf));
  graf->n = n;
  graf->g = (Cvor **)calloc(n, sizeof(Cvor));
  return graf;
}

void dodajNovuGranu(Graf *graf, int u, int v) {
  if (graf->g[u] == NULL) {
    graf->g[u] = noviCvor(v);
    return;
  }
  Cvor *it; // it za iterator, posto iterisemo kroz listu
  // dolazimo do kraja liste (gde je sledeci null)
  for (it = graf->g[u]; it->sledeci != NULL; it = it->sledeci)
    ;
  it->sledeci = noviCvor(v); // dodajemo granu
}

void stampajGraf(Graf *graf) {
  for (int i = 0; i < graf->n; ++i) {
    printf("Lista za cvor %i:\n", i);
    if (graf->g[i] == NULL) {
      printf("\tnull\n");
      continue;
    }
    for (Cvor *it = graf->g[i]; it != NULL; it = it->sledeci)
      printf("\t%i\n", it->vrednost);
  }
}

int main() {
  const int n1 = 4;
  int matrica[4][4] = {{0, 1, 1, 1}, {1, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}};
  printf("Prvi graf prikazan preko matrice susedstva je %s, i njegov max "
         "stepen je %i\n",
         (jeNeusmeren(n1, matrica)) ? "neusmeren" : "usmeren",
         maxStepen(n1, matrica));

  Graf *graf = noviGraf(4);
  dodajNovuGranu(graf, 0, 1);
  dodajNovuGranu(graf, 0, 2);
  dodajNovuGranu(graf, 1, 2);
  dodajNovuGranu(graf, 1, 3);
  dodajNovuGranu(graf, 3, 2);
  stampajGraf(graf);
}
