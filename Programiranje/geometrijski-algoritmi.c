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
int uMnogouglu(Tacka t[], int n, Tacka Q);
float gausova_formula(Tacka arr[], int n);
void zamena(Tacka *A, Tacka *B);
int kvadRastojanje(Tacka A, Tacka B);
void stampajProstMnogougao(Tacka t[], int n);
double max(double a, double b);
double min(double a, double b);
int pripadaDuzi(Tacka P, Tacka Q, Tacka R);
int pripadaOpsegu(Tacka P, Tacka R, Tacka Q);
int sekuSe(Tacka P1, Tacka Q1, Tacka P2, Tacka Q2);

// |A| = sqrt(x^2 + y^2 + z^2)
float intenzitet(Vektor U) { return sqrt(U.x * U.x + U.y * U.y + U.z * U.z); }

// isto, samo sto umesto X koristimo |AB| = sqrt( (B.x - A.x)^2...
float intenzitet_tacka(Tacka A, Tacka B) {
  return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

// A.x A.y
// B.x B.y
// det(A, B) = A.x * B.y - A.y * B.x
float det(Vektor AB, Vektor AC) { return fabs((AB.x * AC.y) - (AB.y * AC.x)); }

// B.x - A.x  B.y - A.y
// C.x - A.x  C.y - A.y
// isto je kao iznad ali u ovom slucaju je P = A, a A = C
// determinanta u 2d vektorima predstavlja povrsinu koju obrazuje paralelogram
float det_tacka(Tacka A, Tacka B, Tacka P) {
  return (A.x - P.x) * (B.y - P.y) - (A.y - P.y) * (B.x - P.x);
}

// determinanta sa apsolutnom vrednoscu za formule
float proizvod(Tacka A, Tacka B, Tacka P) {
  return fabs((A.x - P.x) * (B.y - P.y) - (A.y - P.y) * (B.x - P.x));
}

// Rastojanje tacke P od prave koja prolazi kroz AB
// abs(det(AB, AC))/|AB| je rastojanje
float rastojanje(Tacka A, Tacka B, Tacka P) {
  return proizvod(A, B, P) / intenzitet_tacka(A, B);
}

// AxB odnosno crossproduct
// u 2d je z = 0 pa bi se redukovalo na 2x2 sa samo A i B
// u 3d pravi ortogonalan vektor sa intenzitetom od |A||B|*cos(alpha)
// i    j    k
// A.x  A.y  A.z
// B.x  B.y  B.z
// C.i == C.x => C.x = det(A.y, A.z, B.y, B.z) = A.y*B.z - A.z*B.y
// C.y = A.x*B.z - A.z*B.x ...
void vektorski_proizvod(Vektor a, Vektor b, Vektor *c) {
  c->x = a.y * b.z - a.z * b.y;
  c->y = a.x * b.z - a.z * b.x;
  c->z = a.x * b.y - a.y * b.x;
}

// s obzirom da je proizvod vektora u drugoj dimenziji samo
// pseudo-vektor (u smislu da je fiksan na Y osi), povrsina
// koju pravi trougao medju ta dva vektora je jednaka
// polovini intenziteta istog proizvoda vektora
//(a paralelogram koji vektor cini je samo intenzitet vektorskog proizvoda)
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

// skracena funkcija od iznad, zapravo samo gausova formula
float povrsina(Tacka A, Tacka B, Tacka C) {
  return fabs((B.x * C.y - C.x * B.y) - (A.x * C.y - A.y * C.x) +
              (A.x * B.y - A.y * B.x)) /
         2.0;
}

// Da li su dve tacke sa iste strane duzi AB?
// zato sto je determinanta u 2d samo povrsina sa znakom ( + ili - )
// ako vektor AB ima isti znak za obe determinante onda su sa iste strane
void saIsteStrane(Tacka A, Tacka B, Tacka C, Tacka D) {
  int d1, d2;
  d1 = det_tacka(A, B, C);
  d2 = det_tacka(A, B, D);
  if ((d1 > 0 && d2 > 0) || (d1 < 0 && d2 < 0))
    printf("Tacke su sa istih strana.");
  else
    printf("Nisu sa istih strana.");
}

// ORIJENTACIJA, POCETAK
// racuna se preko linearne funkcije odnosno
// y = kx + n, ako posmatramo dve tacke kao poseban trougao to je
// k1 = AB.y/AB.x == (y2-y1)/(x2-x1)
// k2 = BC.y/BC.x == (y3-y2)/(x3-x2)
int orijentacija_sporije(Tacka P, Tacka Q, Tacka R) {
  float k1, k2;
  k1 = (Q.y - P.y) / (Q.x - P.x);
  k2 = (R.y - Q.y) / (R.x - Q.x);
  if (k1 > k2)
    return 1; // suprotnom smeru kazaljke na satu
  if (k1 < k2)
    return 2; // smer kazaljke na satu
  return 0;
}

// BA.x * CA.y - BA.y * CA.x
orij orijentacija(Tacka A, Tacka B, Tacka C) {
  int d = ((B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x));
  if (d == 0)
    return kolinearne;
  if (d > 0)
    return pozitivna; // suprotnom smeru od kazaljke na satu
  return negativna;   // smeru kazaljke na satu
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
// ORIJENTACIJA, KRAJ

// Da li se tacka Q nalazi u mnogouglu
// iterisemo kroz tacke od min u suprotnom smeru od kazaljke na satu, i
// ako za svake 3 tacke imamo pozitivnu orijentaciju odnosno je na unutrasnjoj
// strani duzi, onda se nalazi u mnogouglu
int uMnogouglu(Tacka t[], int n, Tacka Q) {
  int i;
  for (i = 0; i <= n; i++)
    if (orijentacija(t[i], t[(i + 1) % n], Q) != pozitivna)
      return 0;
  return 1;
}

// Povrsina proizvoljnog n-tougla
float gausova_formula(Tacka arr[], int n) {
  float retval = 0;
  int j = n - 1, i;
  for (i = 0; i < n; ++i) {
    retval += (arr[j].x * arr[i].y) - (arr[i].x * arr[j].y);
    j = i;
  }
  return fabs(retval / 2.0);
}

// GRAHAMOV SKENER, POCETAK
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

  // trazimo najmanju tacku
  for (i = 1; i < n; ++i)
    // ako postoji manji y, ili postoji isti y sa manjim x
    if (t[i].y < ymin || (t[i].y == ymin && t[i].x < t[imin].x)) {
      ymin = t[i].y;
      imin = i;
    }

  // P0 odnosno pocetna tacka nam je P0
  Tacka P0 = t[imin];
  zamena(&t[0], &t[imin]);
  // zamenjujemo zbog i + 1

  for (i = 0; i < n; ++i)
    for (j = i + 1; j < n; ++j) {
      if (orijentacija(P0, t[i], t[j]) ==
          kolinearne) // ako su kolinearne i t[j] je udaljenije od t[i], sortira
                      // se
        if (kvadRastojanje(P0, t[i]) > kvadRastojanje(P0, t[j]))
          zamena(&t[i], &t[j]);

      if (orijentacija(P0, t[i], t[j]) == negativna)
        zamena(&t[i], &t[j]); // ako je negativna samo se sortira
    }

  for (i = 0; i < n; i++)
    printf("(%f, %f)\n", t[i].x, t[i].y);
}
// GRAHAMOV SKENER, KRAJ

// DA LI SE DUZI SEKU, POCETAK
double max(double a, double b) { return (a > b) ? a : b; }
double min(double a, double b) { return (a < b) ? a : b; }

int pripadaDuzi(Tacka P, Tacka Q, Tacka R) {
  int d = ((Q.x - P.x) * (R.y - P.y) - (Q.y - P.y) * (R.x - P.x));
  if (d == 0)
    return 1;
  return 0;
}

int pripadaOpsegu(Tacka P, Tacka R, Tacka Q) { // R izmedju P i Q
  if (R.x >= min(P.x, Q.x) && R.x <= max(P.x, Q.x) && R.y >= min(P.y, Q.y) &&
      R.y <= max(P.y, Q.y))
    return 1;

  return 0;
}

int sekuSe(Tacka P1, Tacka Q1, Tacka P2, Tacka Q2) {
  orij O1, O2, O3, O4;
  O1 = orijentacija(P1, Q1, P2);
  O2 = orijentacija(P1, Q1, Q2);
  O3 = orijentacija(P2, Q2, P1);
  O4 = orijentacija(P2, Q2, Q1);

  if (O1 != O2 && O3 != O4)
    return 1;
  if (O1 == kolinearne && pripadaOpsegu(P1, P2, Q1))
    return 1;
  if (O2 == kolinearne && pripadaOpsegu(P1, Q2, Q1))
    return 1;
  if (O3 == kolinearne && pripadaOpsegu(P2, P1, Q2))
    return 1;
  if (O3 == kolinearne && pripadaOpsegu(P2, Q1, Q2))
    return 1;

  return 0; // u suprotnom se ne seku
}
// DA LI SE DUZI SEKU, KRAJ

int main() {
  Tacka niz[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                 {0, 0}, {1, 2}, {3, 1}, {3, 3}};
  //{ {0,0}, {3,1}, {1,1}, {2,2}, {3,3}, {4,4}, {1,2}, {0,3} }

  stampajProstMnogougao(niz, sizeof(niz) / sizeof(Tacka));
  // Tacka A = {2,2}, B={6,4}, C={4,4}, D = {6,2};
  Tacka A = {1, 1}, B = {1, 4}, C = {1, 2}, D = {1, 5};
  if (sekuSe(A, B, C, D))
    printf("Duzi se seku");
  else
    printf("Duzi se ne seku");

  Tacka P = {0, 0}, Q = {0, 5}, R = {5, 0};
  printf("\npovrsina = %f, povrsina_sporije = %f", povrsina(P, Q, R),
         povrsina_sporije(P, Q, R));

  return 0;
}
