#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum orij { kolinearne, pozitivna, negativna } orij;

typedef struct vektor {
  float x;
  float y;
  float z;
} Vektor;

typedef struct tacka {
  float x;
  float y;
} Tacka;

float intenzitet(Vektor U);
float intenzitet_tacka(Tacka A, Tacka B);
float det(Vektor AB, Vektor AC);
float det_tacka(Tacka A, Tacka B, Tacka P);
float proizvod(Tacka A, Tacka B, Tacka P);
float rastojanje(Tacka A, Tacka B, Tacka P);
float povrsina_sporije(Tacka A, Tacka B, Tacka C);
float povrsina(Tacka A, Tacka B, Tacka C);
void vektorski_proizvod(Vektor a, Vektor b, Vektor *c);
void saIsteStrane(Tacka A, Tacka B, Tacka C, Tacka D);
int orijentacija_sporije(Tacka P, Tacka Q, Tacka R);
orij orijentacija(Tacka A, Tacka B, Tacka C);
void stampajOrijentaciju(orij unos);
int uMnoguglu(Tacka t[], int n, Tacka Q);
float gausova_formula(Tacka arr[], int n);
void zamena(Tacka *A, Tacka *B);
int kvadRastojanje(Tacka A, Tacka B);
void stampajProstMnogougao(Tacka t[], int n);

float intenzitet(Vektor U) { return sqrt(U.x * U.x + U.y * U.y + U.z * U.z); }

float intenzitet_tacka(Tacka A, Tacka B) {
  return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

float det(Vektor AB, Vektor AC) { return fabs((AB.x * AC.y) - (AB.y * AC.x)); }

float det_tacka(Tacka A, Tacka B, Tacka P) {
  return fabs((A.x - P.x) * (B.y - P.y) - (A.y - P.y) + (B.x - P.x));
}

float proizvod(Tacka A, Tacka B, Tacka P) {
  return fabs((A.x - P.x) * (B.y - P.y) - (A.y - P.y) * (B.x - P.x));
}

float rastojanje(Tacka A, Tacka B, Tacka P) {
  return proizvod(A, B, P) / intenzitet_tacka(A, B);
}

float povrsina_sporije(Tacka A, Tacka B, Tacka C) {
  Vektor AB, AC, c;
  AB.x = B.x - A.x;
  AB.y = B.y - A.y;
  AB.z = 0;
  AC.x = C.x - A.x;
  AC.y = C.y - A.y;
  AC.z = 0;
  vektorski_proizvod(AB, AC, &c);
  return 1.0 / 2 * intenzitet(c);
}

float povrsina(Tacka A, Tacka B, Tacka C) {
  return fabs((B.x * C.y - C.x * B.y) - (A.x * C.y - A.y * C.x) +
              (A.x * B.y - A.y * B.x)) /
         2.0;
}

void vektorski_proizvod(Vektor a, Vektor b, Vektor *c) {
  c->x = a.y * b.z - a.z * b.y;
  c->y = a.x * b.z - a.z * b.x;
  c->z = a.x * b.y - a.y * b.x;
}

void saIsteStrane(Tacka A, Tacka B, Tacka C, Tacka D) {
  int d1, d2;
  d1 = det_tacka(A, B, C);
  d2 = det_tacka(A, B, D);
  if ((d1 > 0 && d2 > 0) || (d1 < 0 && d2 < 0))
    printf("Tacke su sa istih strana.");
  else
    printf("Kolinearne su.");
}

int orijentacija_sporije(Tacka P, Tacka Q, Tacka R) {
  float k1, k2;
  k1 = (Q.y - P.y) / (Q.x - P.x);
  k2 = (R.y - Q.y) / (R.x - Q.x);
  if (k1 > k2)
    return 1;
  if (k1 < k2)
    return 2;
  return 0;
}

orij orijentacija(Tacka A, Tacka B, Tacka C) {
  int d = ((B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x));
  if (d == 0)
    return kolinearne;
  if (d > 0)
    return pozitivna;
  return negativna;
}

void stampajOrijentaciju(orij ulaz) {
  switch (ulaz) {
  case 0:
    printf("Kolinearna\n");
    break;
  case 1:
    printf("Pozitivna\n");
    break;
  case 2:
    printf("Negativna\n");
    break;
  }
}

int uMnoguglu(Tacka t[], int n, Tacka Q) {
  int i;
  for (i = 0; i <= n; i++)
    if (orijentacija(t[i], t[(i + 1) % n], Q) != pozitivna)
      return 0;
  return 1;
}

float gausova_formula(Tacka arr[], int n) {
  float retval = 0;
  int j = n - 1, i;
  for (i = 0; i < n; ++i) {
    // retval += (arr[j].X + arr[i].X) * (arr[j].Y - arr[i].Y);
    // (arr[j].X + arr[i].X) * arr[j].Y + (arr[j].X + arr[i].X) * (-arr[i].Y)
    // arr[j].Y*arr[j].X + arr[j].Y*arr[i].X  - arr[i].Y * arr[j].X - arr[i].Y *
    // arr[i].X
    //  (a + b) * (c - d)
    // retval += (arr[j].Y - arr[i].Y)*(arr[j].X + arr[i].X);

    retval += (arr[j].x * arr[i].y) - (arr[i].x * arr[j].y);
    j = i;
  }
  return fabs(retval / 2.0);
}

// dato N tacaka u ravni, takvih da nisu sve kolinearne
// potrebno je povezati prostim mnogouglom

// 1. funkcija koja razmenjuje sadrzaj kordinata za dve tacke (preko pokazivaca)
// tacke su date kao struktura Tacka
// 2. racuna kvadrat rastojanja za 2 tacke, a i b
// 3. koja vraca orijentaciju tacke p1 p2 i p3
// 4. za niz t od n tacaka stampa novi niz tacaka tako da tacke cine prost
// mnogougao
// main. inicijalizovati niz tacaka i pozvati 4. funkciju

void zamena(Tacka *A, Tacka *B) {
  Tacka pom;
  pom = *A;
  *A = *B;
  *B = pom;
}

int kvadRastojanje(Tacka A, Tacka B) {
  return ((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

void stampajProstMnogougao(Tacka t[], int n) {
  int ymin = t[0].y, imin = 0, i, j;

  for (i = 1; i < n; ++i)
    if (t[i].y < ymin || (t[i].y == ymin && t[i].x < t[imin].x)) {
      ymin = t[i].y;
      imin = i;
    }

  Tacka P0 = t[imin];
  zamena(&t[0], &t[imin]);

  for (i = 0; i < n; ++i)
    for (j = i + 1; j < n; j++) {
      if (orijentacija(P0, t[i], t[j]) == kolinearne)
        if (kvadRastojanje(P0, t[i]) > kvadRastojanje(P0, t[j]))
          zamena(&t[i], &t[j]);

      if (orijentacija(P0, t[i], t[j]) == negativna)
        zamena(&t[i], &t[j]);
    }

  for (i = 0; i < n; i++)
    printf("(%f, %f)\n", t[i].x, t[i].y);
}

int main() {
  Tacka niz[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                 {0, 0}, {1, 2}, {3, 1}, {3, 3}};
  //{ {0,0}, {3,1}, {1,1}, {2,2}, {3,3}, {4,4}, {1,2}, {0,3} }

  stampajProstMnogougao(niz, sizeof(niz) / sizeof(Tacka));
  return 0;
}
