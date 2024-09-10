#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //za bitset

int prost1(int n){
    int i=2;
    while(i<=n-1){
        if(n%i==0) return 0;
        i++;
    }
    return 1;
}

int prost2(int n){
    int i=2;
    while(i<=n/2){
        if(n%i==0) return 0;
        i++;
    }
    return 1;
}

int prost3(int n){
    int i=2;
    while(i*i<=n){
        if(n%i==0) return 0;
        i++;
    }
    return 1;
}

int prost1for(int n){
    int i=2;
    for(;i<=n-1;i++){
        if(n%i==0) return 0;
    }
    return 1;
}

int prost2for(int n){
    int i=2;
    for(;i<=n/2;i++){
        if(n%i==0) return 0;
    }
    return 1;
}

int prost3for(int n){
    int i=2;
    for(;i*i<=n;i++){
        if(n%i==0) return 0;
    }
    return 1;
}

void EratostenovoSito(int n, bool* stanja){ //nalazi sve brojeve od 1 do N
  int i, p=2;
  for(;p*p<=n;p++){
    if(stanja[p] == false) {
      for (i =p*p; i<=n; i+=p)
        stanja[i] = true;
    }
  }
  for (p = 2; p <= n; p++)
    if(!stanja[p])
      printf("%d ",p);
}

int euklidovRec(int a, int b){
  if(a == 0)
    return b;
  return euklidovRec(b%a, a);
}

int euklidov(int a, int b){
  while(b!=0){
    int pom = b;
    b = a%b;
    a = pom;
  }
  return a;
}

//obican euklidov algoritam pronalazi samo nzd, a prosireni takodje nalazi brojeve x i y
//ax+by = nzd(a,b)
//uzajamno prosti brojevi su oni ciji je nzd 1
//nalazi dva cela broja x i y od kojih ce uglavnom jedan biti negativan, koji sluzi za bezuovu teoremu
int prosirenEuklidov(int a, int b, int *x, int *y){
    if(a == 0){
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1; //ovde cuvamo podatke koje dobijemo iz rekurzije
    int rec = prosirenEuklidov(b%a, a, &x1, &y1);

    *x = y1 - (b/a) * x1; //nzd(a,b) = rec, iz formule ax+by = rec onda x = (rec-by)/a 
    *y = x1; //ax + by iz funkcije je takodje ax+by = (b%a)x1 + ay1, sto je ax + by = a(y1 - [b/a]*x1)+bx1
             //onda sledi da je x=y1-[b/a]*x1

    return rec;
}

//nalazi uzajamno proste brojeve sa brojem N
int eulerova(int n){
  int rezultat = 0, i=1;
  for(;i<=n;i++){
    if(euklidov(i, n) == 1){
      ++rezultat;
    }
  }
  return rezultat;
}

void prostiCinioci(int n){
  while(n%2==0){
    printf("%d ", 2);
    n=n/2;
  }

  int i=3;
  for(;i*i<=n;i=i+2){
    while(n%i==0){
      printf("%d ", i);
      n=n/i;
    }
  }

  if(n>2)
    printf("%d ", n);
}

//rastavljanje broja na proste cinioce
int main(){
  int n, a, b, x, y, NZD;
  printf("Unesite broj: ");
  scanf("%i", &n);

  (prost1(n) && prost2(n) && prost3(n) && prost1for(n) && prost2for(n) && prost3for(n))?printf("Prost broj.\n"):printf("Nije prost broj.\n");

  printf("Unesi broj do koga se traze prosti: ");
  scanf("%i", &n);
  bool* prosti = (bool*)calloc(n, sizeof(bool));
  EratostenovoSito(n, prosti);
  printf("\nProsti cinioci broja %i su: ", n);
  prostiCinioci(n);


  printf("\nPo eulerovom algoritmu,\nbroj uzajamno prostih brojeva sa N je: %i", eulerova(n));


  printf("\nUnesi A za euklidov algoritam: ");
  scanf("%i", &a);
  printf("Unesi B: ");
  scanf("%i", &b);
  NZD = prosirenEuklidov(a, b, &x, &y);
  printf("\nNZD: %i\n X: %i\n y: %i", NZD, x, y);


  return 0;
}
