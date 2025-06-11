#include <stdio.h>
#include <stdlib.h>

typedef struct cvor {
  int vrednost;
  struct cvor *sledeci; 
} Cvor;
Cvor *noviCvor(int vrednost);
void stampajCvor(Cvor *cvor);

typedef struct graf {
  int n;
  Cvor **g;
} Graf;
Graf *noviGraf(int n);
void dodajNaGraf(Graf *graf, int u, int v);
void stampajGraf(Graf *graf);
void saCasaBriseGranuGraf(Graf *graf, int u, int v);
void briseGranuGraf(Graf *graf, int u, int v);
int postojiGranaGraf(Graf *graf, int u, int v);

typedef struct grafx {
  int n;
  Cvor **g;
  int* vidjeno;
} Grafx;
Grafx *noviGrafx(int n);
void dodajNaGrafx(Grafx *graf, int u, int v);

#define MAX 128
typedef struct red {
  int podaci[MAX];
  int front;
  int rear;
} Red;
Red *noviRed();
int jePrazanRed(Red *q);
void dodajNaRed(Red *q, int v);
int uzmiSaRed(Red *q);
void stampajRed(Red *q);

int jeNeusmeren(int n, int g[n][n]);
int jeUsmeren(int n, int g[n][n]);
int maxStepen(int n, int g[n][n]);
int minStepen(int n, int g[n][n]);
int sumStepen(int n, int g[n][n]);
int brIz(int n, int g[n][n], int u);
int brUl(int n, int g[n][n], int v);
int brPetlja(int n, int g[n][n]);
int brIzGraf(Cvor *cvor);
int brUlGraf(Graf *graf, int v);
int brPetljaGraf(Graf *graf);

void bfs(int n, int g[n][n], int u);
void bfsGraf(Graf *graf, int u);
int bfsPostojiPut(int n, int g[n][n], int u, int v);
int bfsPostojiPutGraf(Graf *graf, int u, int v);

void dfs(int n, int g[n][n], int u, int vidjeno[n]);
void dfsGrafx(Grafx* graf, int u);

void dajkstra(int n, int g[n][n], int u);

int main() {
#define n1 4
  // umesto define n1, mozete da imate int n1 = 4;
  // ali ce to da zahteva da pisete int matrica[4][4] umesto n1 n1
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
  dodajNaGraf(graf, 0, 1);
  dodajNaGraf(graf, 0, 2);
  dodajNaGraf(graf, 1, 2);
  dodajNaGraf(graf, 1, 3);
  dodajNaGraf(graf, 3, 2);
  stampajGraf(graf);
  printf("Petlje u grafu: %i\n", brPetljaGraf(graf));

  stampajCvor(graf->g[0]);
  printf("Izlazni: %i\nUlazni: %i\n", brIzGraf(graf->g[0]), brUlGraf(graf, 0));

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
  bfsGraf(graf, 0);
  printf("Matrica2: Da li postoji put izmedju 0 i 5: %s\n", bfsPostojiPut(n2, matrica2, 0, 5)?"da":"ne");
  printf("Matrica2: Da li postoji put izmedju 5 i 0: %s\n", bfsPostojiPut(n2, matrica2, 5, 0)?"da":"ne");
  printf("Graf: Da li postoji put izmedju 0 i 3: %s\n", bfsPostojiPutGraf(graf, 0, 3)?"da":"ne");
  printf("Graf: Da li postoji put izmedju 3 i 0: %s\n", bfsPostojiPutGraf(graf, 3, 0)?"da":"ne");

  Grafx *grafx = noviGrafx(4);
  dodajNaGrafx(grafx, 0, 1);
  dodajNaGrafx(grafx, 0, 2);
  dodajNaGrafx(grafx, 1, 2);
  dodajNaGrafx(grafx, 1, 3);
  dodajNaGrafx(grafx, 3, 2);
  printf("DFS obilazak grafa:\n");
  dfsGrafx(grafx,0);

#define n3 4
  int matrica3[n3][n3] = {
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 1, 0}
  };
  printf("DFS obilazak grafa:\n");
  {
  int vidjeno[n3] = {0};
  dfs(n3, matrica3, 0, vidjeno);
  }

#define n4 5
#define INF 2000000000 //max 32 int ali zaokruzen na najvecu jedinicu
  int tezinska_matrica[n4][n4] = {
    {0,6,INF,1,INF},
    {6,0,5,2,2},
    {INF,5,0,2,2},
    {1,2,INF,0,1},
    {INF,2,6,1,0}
  };
  dajkstra(n4, tezinska_matrica, 0);
  return 0;
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
  graf->g = (Cvor **)calloc(n, sizeof(Cvor*));
  return graf;
}

void dodajNaGraf(Graf *graf, int u, int v) {
  if (graf->g[u] == NULL) {
    graf->g[u] = noviCvor(v);
    return;
  }
  Cvor *it;
  for (it = graf->g[u]; it->sledeci != NULL; it = it->sledeci)
    ;
  it->sledeci = noviCvor(v);
}

void stampajGraf(Graf *graf) {
  for (int i = 0; i < graf->n; ++i) {
    printf("Lista za cvor %i:\n", i);
    for (Cvor *it = graf->g[i]; it != NULL; it = it->sledeci)
      printf("\t%i\n", it->vrednost);
    printf("\tnull\n");
  }
}

void saCasaBriseGranuGraf(Graf *graf, int u, int v) {
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

void briseGranuGraf(Graf *graf, int u, int v) {
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

int postojiGranaGraf(Graf *graf, int u, int v) {
  for (Cvor *cvor = graf->g[u]; cvor != NULL; cvor = cvor->sledeci)
    if (cvor->vrednost == v)
      return 1;
  return 0;
}

Grafx *noviGrafx(int n) {
  Grafx *graf = (Grafx *)malloc(sizeof(Grafx));
  graf->n = n;
  graf->g = (Cvor **)calloc(n, sizeof(Cvor*));
  graf->vidjeno = (int*)calloc(n, sizeof(int));
  return graf;
}

void dodajNaGrafx(Grafx *graf, int u, int v) {
  if (graf->g[u] == NULL) {
    graf->g[u] = noviCvor(v);
    return;
  }
  Cvor *it; 
  for (it = graf->g[u]; it->sledeci != NULL; it = it->sledeci)
    ;
  it->sledeci = noviCvor(v);
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
  int i, j, tr = 0, min = 0xffffffff;
  for (i = 0; i < n; ++i, tr = 0) {
    for (j = 0; j < n; ++j)
      if (g[i][j])
        ++tr;
    min = (tr < min) ? tr : min;
  }
  return min;
}

int sumStepen(int n, int g[n][n]) {
  int i, j, br = 0;
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
      if (g[i][j] == 1)
        ++br;
  return br;
}

int brIz(int n, int g[n][n], int u) {
  int j, br = 0;
  for (j = 0; j < n; ++j)
    if (g[u][j] == 1)
      ++br;
  return br;
}

int brUl(int n, int g[n][n], int v) {
  int i, br = 0;
  for (i = 0; i < n; ++i)
    if (g[i][v] == 1)
      ++br;
  return br;
}

int brPetlja(int n, int g[n][n]){
  int br = 0, i;
  for(i = 0; i < n; ++i)
    if(g[i][i])
      ++br;
  return br;
}

int brIzGraf(Cvor *cvor) {
  int br = 0;
  for (; cvor != NULL; cvor = cvor->sledeci)
    ++br;
  return br;
}

int brUlGraf(Graf *graf, int v) {
  int i, br = 0;
  for (i = 0; i < graf->n; ++i)
    for (Cvor *it = graf->g[i]; it != NULL; it = it->sledeci)
      if (it->vrednost == v) {
        ++br;
        break;
      }
  return br;
}

int brPetljaGraf(Graf *graf) {
  int i, br = 0;
  for (i = 0; i < graf->n; ++i)
    for (Cvor *it = graf->g[i]; it != NULL; it = it->sledeci)
      if (it->vrednost == i) {
        ++br;
        break;
      }
  return br;
}


void bfs(int n, int g[n][n], int u) {
  int j, cvor;
  int vidjeno[n];
  for (j = 0; j < n; ++j)
    vidjeno[j] = 0;
  // alternativno, memset(vidjeno, 0, n*sizeof(int));

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

void bfsGraf(Graf *graf, int u) {
  Cvor *cvor;
  int j, vidjeno[graf->n];
  for (j = 0; j < graf->n; ++j)
    vidjeno[j] = 0;

  Red *q = noviRed();
  dodajNaRed(q, u);
  vidjeno[u] = 1;

  printf("BFS obilazak liste susedstva:\n%i, ", u);
  while (!jePrazanRed(q))
    for (cvor = graf->g[uzmiSaRed(q)]; cvor != NULL; cvor = cvor->sledeci)
      if (!vidjeno[cvor->vrednost]) {
        dodajNaRed(q, cvor->vrednost);
        vidjeno[cvor->vrednost] = 1;
        printf("%i, ", cvor->vrednost);
      }
  printf("\b\b \n");
  free(q);
}

int bfsPostojiPutGraf(Graf *graf, int u, int v) {
  Cvor *cvor;
  int j, vidjeno[graf->n];
  for (j = 0; j < graf->n; ++j)
    vidjeno[j] = 0;

  Red *q = noviRed();
  dodajNaRed(q, u);
  vidjeno[u] = 1;

  while (!jePrazanRed(q))
    for (cvor = graf->g[uzmiSaRed(q)]; cvor != NULL; cvor = cvor->sledeci)
      if (cvor -> vrednost == v)
        return 1;
      else if (!vidjeno[cvor->vrednost]) {
        dodajNaRed(q, cvor->vrednost);
        vidjeno[cvor->vrednost] = 1;
      }
  free(q);
  return 0;
}


void dfs(int n, int g[n][n], int u, int vidjeno[n]){
  vidjeno[u] = 1;
  printf("\t%i\n", u);
  for(int i = 0; i < n; ++i)
    if(!vidjeno[i] && g[u][i])
      dfs(n,g,i,vidjeno);
}

void dfsGrafx(Grafx* graf, int u){
    graf->vidjeno[u] = 1;
    printf("\t%i\n", u);
    for(Cvor* cvor = graf->g[u]; cvor != NULL; cvor = cvor -> sledeci)
        if(!graf->vidjeno[cvor->vrednost])
            dfsGrafx(graf,cvor->vrednost);
}

void dajkstra(int n, int t[n][n], int start){
  int i, j, k, min, next, prev[n], dist[n];
  int visited[n];

  for(i = 0; i < n; ++i){
    dist[i] = t[start][i];
    prev[i] = start;
    visited[i] = 0;
  }

  dist[start] = 0;
  visited[start] = 1;

  for(k = 1; k < n; ++k){
    min = INF;

    for(i = 0; i < n; ++i)
      if(!visited[i] && dist[i] < min){
        min = dist[i];
        next = i;
      }

    if(min == INF) break;

    visited[next] = 1;
    for(i = 0; i < n; ++i)
      if(!visited[i] && dist[i] > dist[next]+t[next][i]){
        dist[i] = dist[next] + t[next][i];
        prev[i] = next;
      }
  }

  printf("Nizovi dist i prev\ndist: ");
  for(i = 0; i < n; ++i)
    printf("%d ", dist[i]);
  printf("\nprev: ");
  for(i = 0; i < n; ++i)
    printf("%d ", prev[i]);
}
