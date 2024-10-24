#include <math.h>
#include <stdbool.h> //za bitset
#include <stdio.h>
#include <stdlib.h>

int prost1(int n) {
  int i = 2;
  while (i <= n - 1) {
    if (n % i == 0)
      return 0;
    i++;
  }
  return 1;
}

int prost2(int n) {
  int i = 2;
  while (i <= n / 2) {
    if (n % i == 0)
      return 0;
    i++;
  }
  return 1;
}

int prost3(int n) {
  int i = 2;
  while (i * i <= n) {
    if (n % i == 0)
      return 0;
    i++;
  }
  return 1;
}

int prost1for(int n) {
  int i = 2;
  for (; i <= n - 1; i++) {
    if (n % i == 0)
      return 0;
  }
  return 1;
}

int prost2for(int n) {
  int i = 2;
  for (; i <= n / 2; i++) {
    if (n % i == 0)
      return 0;
  }
  return 1;
}

int prost3for(int n) {
  int i = 2;
  for (; i * i <= n; i++) {
    if (n % i == 0)
      return 0;
  }
  return 1;
}

// svaki broj moze da se predstavi kao n = p1^k1 * p2^k2....
// gde su p prosti cinioci a k eksponenti
int sumaDelioca1(int n) {
  int i = 2, s = 1 + n;
  for (; i < n; i++)
    if (n % i == 0)
      s = s + i;
  return s;
}

int sumaDelioca2(int n) {
  int i = 2, s = 1 + n;
  for (; i < n / 2; i++)
    if (n % i == 0)
      s = s + i;
  return s;
}

int sumaDelioca3(int n) {
  int i = 1, s = 0;
  for (; i * i <= n; i++) {
    if (n % i == 0) {
      s += i;
      if (i != n / i) {
        s += n / i;
      }
    }
  }
  return s;
}

int sumaDelioca4(int n) {
  int i = 1, s = 0;
  for (; i * i <= n; ++i) {
    if (n % i == 0) {
      s += i + n / i;
    }
  }
  i--;
  if (i * i == n)
    s -= n / i;
  return s;
}

int brojDelioca(int n) {
  int i = 1, br = 0;
  for (; i * i <= n; i++)
    if (n % i == 0) {
      if (n == i * i)
        br++;
      else
        br = br + 2;
    }
  return br;
}

void sumabrojDelioca(int n, int *s, int *b) {
  int i = 1;
  *b = 2;
  *s = 0;
  for (; i * i <= n; ++i) {
    if (n % i == 0) {
      *s += i + n / i;
      *b = *b + 1;
    }
  }
  i--;
  if (i * i == n) {
    *s -= n / i;
    *b = *b - 1;
  }
}

int EratostenovoSito_SumaDelioca(int n) {
  int i, br, j, prost[n + 1], suma = 1;
  for (i = 0; i <= n; i++)
    prost[i] = 1;

  prost[0] = prost[1] = 0;

  for (i = 2; i * i <= n; i++)
    if (prost[i] == 1)
      for (j = i * i; j <= n; j = j + i)
        prost[j] = 0;

  for (i = 2; i <= n; i++)
    if (prost[i] == 1) {
      br = 0;
      while (n % i == 0) {
        n = n / i;
        br++;
      }
      suma = suma * ((pow(i, br + 1) - 1) / (i - 1));
    }
  return suma;
}

int EratostenovoSito_BrojDelioca(int n) {
  int i, br, j, prost[n + 1], broj = 1;

  for (i = 0; i <= n; i++)
    prost[i] = 1;

  prost[0] = prost[1] = 0;

  for (i = 2; i * i <= n; i++)
    if (prost[i] == 1)
      for (j = i * i; j <= n; j = j + i)
        prost[j] = 0;

  for (i = 2; i <= n; i++)
    if (prost[i] == 1) {
      br = 0;
      while (n % i == 0) {
        n = n / i;
        br++;
      }
      broj *= (1 + br);
    }
  return broj;
}

void EratostenovoSito(int n, bool *stanja) { // nalazi sve brojeve od 1 do N
  int i, p = 2;

  for (; p * p <= n; p++) {
    if (stanja[p] == false) {
      for (i = p * p; i <= n; i += p)
        stanja[i] = true;
    }
  }

  for (p = 2; p <= n; p++)
    if (!stanja[p])
      printf("%d ", p);
}

/*
sastaviti funkciju koja ispisuje sve prosto cinioce broja N
preko eratostenovog sita
*/
void EratostenovoSito_IspisProstihCinioca(
    int n, int *stanja) { // nalazi sve brojeve od 1 do N
  int i, p = 2;
  for (i = 0; i < n; i++)
    stanja[i] = i;

  for (; p * p <= n; p++) {
    if (stanja[p] == p) {
      for (i = p * p; i <= n; i += p)
        stanja[i] = p;
    }
  }

  while (n > 1) {
    printf("%i ", stanja[n]);
    n = n / stanja[n];
  }
}

int euklidovRec(int a, int b) {
  if (a == 0)
    return b;
  return euklidovRec(b % a, a);
}

int euklidov(int a, int b) {
  while (b != 0) {
    int pom = b;
    b = a % b;
    a = pom;
  }
  return a;
}

int NZS(int a, int b) {
  return (a * b) / euklidov(a, b); // euklidov je NZD
}

// obican euklidov algoritam pronalazi samo nzd, a prosireni takodje nalazi
// brojeve x i y ax+by = nzd(a,b) uzajamno prosti brojevi su oni ciji je nzd 1
// nalazi dva cela broja x i y od kojih ce uglavnom jedan biti negativan, koji
// sluzi za bezuovu teoremu
int prosirenEuklidov(int a, int b, int *x, int *y) {
  if (a == 0) {
    *x = 0;
    *y = 1;
    return b;
  }

  int x1, y1; // ovde cuvamo podatke koje dobijemo iz rekurzije
  int rec = prosirenEuklidov(b % a, a, &x1, &y1);

  *x =
      y1 - (b / a) *
               x1; // nzd(a,b) = rec, iz formule ax+by = rec onda x = (rec-by)/a
  *y = x1; // ax + by iz funkcije je takodje ax+by = (b%a)x1 + ay1, sto je ax +
           // by = a(y1 - [b/a]*x1)+bx1 onda sledi da je x=y1-[b/a]*x1

  return rec;
}

// nalazi uzajamno proste brojeve sa brojem N
int eulerova(int n) {
  int rezultat = 0, i = 1;
  for (; i <= n; i++) {
    if (euklidov(i, n) == 1) {
      ++rezultat;
    }
  }
  return rezultat;
}

void prostiCinioci(int n) {
  while (n % 2 == 0) {
    printf("%d ", 2);
    n = n / 2;
  }

  int i = 3;
  for (; i * i <= n; i = i + 2) {
    while (n % i == 0) {
      printf("%d ", i);
      n = n / i;
    }
  }

  if (n > 2)
    printf("%d ", n);
}

int main_geometrijski()
{
    int x[3];
    int y[3];
    int i;


    float det, p;
    for(i=(int)'A';i<(int)'D';i++){
        printf("Unesite %cx, onda %cy: ", i, i);
        scanf("%i", &x[i-'A']);
        scanf("%i", &y[i-'A']);
    }
    det = (x[1] - x[0])*(y[2]-y[0]) - (y[1] - y[0])*(x[2]-x[0]);

    p = abs(det)/2.0;
    printf("Povrsina je %f\n", p);
    if(det > 0)
        printf("Pozitivna");
    else if(det == 0) printf("Kolinearna");
    else printf("Negativna");
    return 0;
} // TODO: geometrijski algoritmi, poseban fajl

// rastavljanje broja na proste cinioce
int main() {
  int n, a, b, x, y, NZD;
  printf("Unesite broj: ");
  scanf("%i", &n);

  (prost1(n) && prost2(n) && prost3(n) && prost1for(n) && prost2for(n) &&
   prost3for(n))
      ? printf("Prost broj.\n")
      : printf("Nije prost broj.\n");

  printf("Unesi broj do koga se traze prosti: ");
  scanf("%i", &n);
  bool *prosti = (bool *)calloc(n, sizeof(bool));
  int *prosti_cinioci = (int *)malloc(n * sizeof(int));
  EratostenovoSito(n, prosti);
  printf("\nProsti cinioci broja %i su: ", n);
  EratostenovoSito_IspisProstihCinioca(n, prosti_cinioci);
  printf("\nProsti cinioci broja %i su: ", n);
  prostiCinioci(n);

  printf("\nSuma delioca broja %i su: %i", n, sumaDelioca4(n));
  int br, s;
  sumabrojDelioca(n, &s, &br);
  printf("\nSuma delioca broja %i a broj delioca je %i\n", s, br);

  printf("\nPo eulerovom algoritmu, broj uzajamno prostih brojeva sa N je: %i",
         eulerova(n));

  printf("\nUnesi A za euklidov algoritam: ");
  scanf("%i", &a);
  printf("Unesi B: ");
  scanf("%i", &b);
  NZD = prosirenEuklidov(a, b, &x, &y);
  printf("\nNZD: %i\n X: %i\n y: %i", NZD, x, y);

  return 0;
}
