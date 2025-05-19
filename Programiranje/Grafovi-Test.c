#include <stdio.h>
#include <stdlib.h>

typedef struct cvor {
  int vrednost;
  struct cvor *sledeci;
} Cvor;

typedef struct graf {
  int n;
  Cvor **g;
} Graf;

#define MAX 128
typedef struct red {
  int podaci[MAX];
  int front;
  int rear;
} Red;

int jeNeusmeren(int n, int g[n][n]);
int jeUsmeren(int n, int g[n][n]);
int maxStepen(int n, int g[n][n]);
int minStepen(int n, int g[n][n]);
Cvor *noviCvor(int vrednost);
void stampajCvor(Cvor *cvor);
Graf *noviGraf(int n);
void dodajNovuGranu(Graf *graf, int u, int v);
void stampajGraf(Graf *graf);
int BrIz(Cvor *cvor);
int BrUl(Graf *graf, int v);
int BrPetlja(Graf *graf);
void saCasa_brise(Graf *graf, int u, int v);
void brise(Graf *graf, int u, int v);
int postojiGrana(Graf *graf, int u, int v);
Red *noviRed();
int jePrazanRed(Red *q);
void dodajNaRed(Red *q, int v);
int uzmiSaRed(Red *q);
void stampajRed(Red *q);
int stepen(int n, int g[n][n]);
int BrIzCvora(int n, int g[n][n], int u);
int BrUlCvora(int n, int g[n][n], int v);
void bfs(int n, int g[n][n], int u);
int bfsPostojiPut(int n, int g[n][n], int u, int v);

// clang-format off

int main() {
#define n1 4
  int matrica1[n1][n1] = {
    {0, 1, 1, 1},
    {1, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1}};

  printf("Prvi graf prikazan preko matrice susedstva je %s, "
         "i njegov max stepen je %i\n",
         (jeNeusmeren(n1, matrica1)) ? "neusmeren" : "usmeren",
         maxStepen(n1, matrica1));

  Graf *graf = noviGraf(4);
  dodajNovuGranu(graf, 0, 1);
  dodajNovuGranu(graf, 0, 2);
  dodajNovuGranu(graf, 1, 2);
  dodajNovuGranu(graf, 1, 3);
  dodajNovuGranu(graf, 3, 2);
  stampajGraf(graf);
  printf("Petlje u grafu: %i\n", BrPetlja(graf));

  stampajCvor(graf->g[0]);
  printf("Izlazni: %i\nUlazni: %i\n", BrIz(graf->g[0]), BrUl(graf, 0));

  Red *red = noviRed();
  dodajNaRed(red, 1);
  dodajNaRed(red, 2);
  dodajNaRed(red, 3);
  dodajNaRed(red, 4);
  dodajNaRed(red, 5);
  stampajRed(red);

#define n2 6
  int matrica2[n2][n2] = {
      {0, 1, 1, 0, 0, 0},
      {0, 0, 1, 1, 0, 0},
      {0, 0, 0, 1, 1, 0},
      {0, 0, 1, 0, 0, 0},
      {0, 0, 0, 1, 0, 1}, 
      {0, 1, 1, 0, 0, 0}};

  bfs(n2, matrica2, 0);
  printf("Da li postoji put izmedju 0 i 5: %s\n", bfsPostojiPut(n2, matrica2, 0, 5)?"da":"ne");
  printf("Da li postoji put izmedju 5 i 0: %s\n", bfsPostojiPut(n2, matrica2, 5, 0)?"da":"ne");
}

int jeNeusmeren(int n, int g[n][n]) {
  int i, j;
  for (i = 0; i < n; ++i)
    for (j = i + 1; j < n; ++j)
      if (g[i][i] == 1)
        return 0;
      else if (g[i][j] != g[j][i])
        return 0;
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
  int i, j, tr = 0, min = 0;
  for (i = 0; i < n; ++i, tr = 0) {
    for (j = 0; j < n; ++j)
      if (g[i][j])
        ++tr;
    min = (tr < min) ? tr : min;
  }
  return min;
}


Cvor *noviCvor(int vrednost) {
  Cvor *novi = (Cvor *)malloc(sizeof(Cvor));
  novi->vrednost = vrednost;
  novi->sledeci = NULL;
  return novi;
}

void stampajCvor(Cvor *cvor) {
  printf("Cvor: \n");
  for (; cvor != NULL; cvor = cvor->sledeci)
    printf("\t%i\n", cvor->vrednost);
  printf("\tnull\n");
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

  Cvor *it;
  for (it = graf->g[u]; it->sledeci != NULL; it = it->sledeci)
    ;
  it->sledeci = noviCvor(v); // dodajemo granu
}

void stampajGraf(Graf *graf) {
  for (int i = 0; i < graf->n; ++i) {
    printf("Lista za cvor %i:\n", i);
    for (Cvor *it = graf->g[i]; it != NULL; it = it->sledeci)
      printf("\t%i\n", it->vrednost);
    printf("\tnull\n");
  }
}

int BrIz(Cvor *cvor) {
  int br = 0;
  for (; cvor != NULL; cvor = cvor->sledeci)
    ++br;
  return br;
}

int BrUl(Graf *graf, int v) {
  int i, br = 0;
  for (i = 0; i < graf->n; ++i)
    for (Cvor *it = graf->g[i]; it != NULL; it = it->sledeci)
      if (it->vrednost == v) {
        ++br;
        break;
      }
  return br;
}

int BrPetlja(Graf *graf) {
  int i, br = 0;
  for (i = 0; i < graf->n; ++i)
    for (Cvor *it = graf->g[i]; it != NULL; it = it->sledeci)
      if (it->vrednost == i) { // ako je grana sa samim sobom
        ++br;
        break;
      }
  return br;
}



void saCasa_brise(Graf *graf, int u, int v) {
  Cvor *pre = graf->g[u];

  if (pre == NULL)
    return;

  if (pre->vrednost == v) {
    graf->g[u] = pre->sledeci;
    free(pre);
    return;
  }

  Cvor *tek = pre->sledeci;

  while (tek != NULL)
    if (tek->vrednost == v) {
      pre->sledeci = tek->sledeci;
      free(tek);
      return;
    } else {
      pre = tek;
      tek = tek->sledeci;
    }
}

void brise(Graf *graf, int u, int v) {
  Cvor *it = graf->g[u];

  if (it != NULL && it->vrednost == v) {
    graf->g[u] = it->sledeci;
    free(it);
    return;
  }

  for (; it->sledeci != NULL; it = it->sledeci) {
    if (it->sledeci->vrednost == v) {
      Cvor *grana = it->sledeci;
      it->sledeci = it->sledeci->sledeci;
      free(grana);
      return;
    }
  }
}

int postojiGrana(Graf *graf, int u, int v) {
  for (Cvor *cvor = graf->g[u]; cvor != NULL; cvor = cvor->sledeci)
    if (cvor->vrednost == v)
      return 1;
  return 0;
}


Red *noviRed() {
  Red *q = (Red *)malloc(sizeof(Red));
  q->front = -1;
  q->rear = -1;
  return q;
}

int jePrazanRed(Red *q) {
  if (q->rear == -1)
    return 1;
  return 0;
}

void dodajNaRed(Red *q, int v) {
  if (q->rear >= MAX - 1) {
    printf("Red je pun");
    return;
  }

  ++(q->rear);
  q->podaci[q->rear] = v;
  q->front = (q->front < 0) ? 0 : q->front;
}


int uzmiSaRed(Red *q) {
  if (q->rear == -1) {
    printf("Red je prazan");
    return -1;
  }

  int vrednost = q->podaci[q->front];

  if (q->front == q->rear)
    q->front = q->rear = -1;
  else
    ++q->front;

  return vrednost;
}

void stampajRed(Red *q) {
  printf("Red:\n");
  if (jePrazanRed(q)) {
    printf("\tPrazan red");
    return;
  }

  for (int i = q->front; i <= q->rear; ++i)
    printf("\t%i\n", q->podaci[i]);
}

int stepen(int n, int g[n][n]) {
  int i, j, br = 0;
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
      if (g[i][j] == 1)
        ++br;
  return br;
}

int BrIzCvora(int n, int g[n][n], int u) {
  int j, br = 0;
  for (j = 0; j < n; ++j)
    if (g[u][j] == 1)
      ++br;
  return br;
}

int BrUlCvora(int n, int g[n][n], int v) {
  int i, br = 0;
  for (i = 0; i < n; ++i)
    if (g[i][v] == 1)
      ++br;
  return br;
}

void bfs(int n, int g[n][n], int u) {
  int j, cvor;
  int vidjeno[n];
  for (j = 0; j < n; ++j)
    vidjeno[j] = 0;

  Red *q = noviRed();
  dodajNaRed(q, u);
  vidjeno[u] = 1;

  printf("BFS obilazak matrice susedstva:\n");
  while (!jePrazanRed(q)) {
    cvor = uzmiSaRed(q);
    for (j = 0; j < n; ++j)
      if (!vidjeno[j] && g[cvor][j]) {
        dodajNaRed(q, j);
        vidjeno[j] = 1;
        printf("\t%i -> %i\n", cvor, j);
      }
  }
  free(q);
}

int bfsPostojiPut(int n, int g[n][n], int u, int v) {
  int j, cvor;
  int vidjeno[n];
  for (j = 0; j < n; ++j)
    vidjeno[j] = 0;

  Red *q = noviRed();
  dodajNaRed(q, u);
  vidjeno[u] = 1;

  while (!jePrazanRed(q)) {
    cvor = uzmiSaRed(q);

    if (g[cvor][v])
      return 1;
    for (j = 0; j < n; ++j)
      if (!vidjeno[j] && g[cvor][j]) {
        dodajNaRed(q, j);
        vidjeno[j] = 1;
      }
  }
  free(q);
  return 0;
}

