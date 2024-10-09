#include <math.h> //opcionalno ako vam treba za koren ili sumu delioca preko eratostena
#include <stdio.h>
#include <stdlib.h>
// optimalna provera da li je jedan broj prost
//
// PREDZNANJE: Ojlerov/Eulerov algoritam trazi NZD
//             Euklidov algoritam trazi uzajamno proste brojeve s brojem N
int prost(int n) {
  int i = 2;
  while (i * i <= n) {
    if (n % i == 0)
      return 0;
    i++;
  }
  return 1;
}

// isto optimalna provera ali je for ciklus umesto while
int prost3for(int n) {
  int i = 2;
  for (; i * i <= n; i++) {
    if (n % i == 0)
      return 0;
  }
  return 1;
}

// najoptimalnija suma delioca jednog broja sto smo radili u skolu
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

// funkcija koja vraca sumu i broj delioca sa pokazivaci,
// ovo je moj nacin i nije od cas
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

// dve vrste od euklidov algoritam, rekurzivni pa iterativni
// koristi se za NZD
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

// JEDINI eulerov/ojlerov algoritam, prosireni se NE uci
// koristi se za trazenje uzajamno prosti brojevi
int eulerova(int n) {
  int rezultat = 0, i = 1;
  for (; i <= n; i++) {
    if (euklidov(i, n) == 1) {
      ++rezultat;
    }
  }
  return rezultat;
}

// Ispisuje svi prosti cinioci bez eratostenovog sita
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

// TRI VRSTE od primenjen eratostenov algoritam, svaki ima posebnu svrhu
// svrha je napisana u ime funkciju
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

void EratostenovoSito_IspisProstihBrojeva_od_0_do_N(
    int n, int *stanja) { // nalazi sve brojeve od 1 do N
  int i, p = 2;

  for (; p * p <= n; p++) {
    if (stanja[p] == 0) {
      for (i = p * p; i <= n; i += p)
        stanja[i] = 1;
    }
  }

  for (p = 2; p <= n; p++)
    if (!stanja[p])
      printf("%d ", p);
}

void EratostenovoSito_IspisProstihCinioca_broja_N(
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
