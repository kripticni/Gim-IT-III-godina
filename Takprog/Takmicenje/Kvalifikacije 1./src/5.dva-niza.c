#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N;

// unsigned long long vrednost_podniza(int L, int R, unsigned int A[N],
//                                    unsigned int B[N], unsigned int
//                                    prosli_and);

unsigned long long iterativno(int L, int R, unsigned int A[N],
                              unsigned int B[N], int N) {
  int i = 0, j;
  unsigned int xor, and, max = (A[0] ^ A[1]) * (B[0] ^ B[1]), provera;

  xor = A[0];
  for (i = 0; i < N - 1; i++) {
    // xor ^= A[i + 1];
    and = B[i] & B[i + 1];
    xor = A[i] ^ A[i + 1];
    for (j = i + 1; j < N; j++) {
      xor ^= A[j];
      and &= B[j];
      provera = xor*and;
      if (provera > max)
        max = provera;
    }
    // xor ^= A[i];
  }
  return max;
}

unsigned long long rekurzivno(int L, int R, unsigned int A[N],
                              unsigned int B[N], unsigned int xor,
                              unsigned int and, int N);

unsigned long long podniz(int L, int R, unsigned A[N], unsigned B[N],
                          unsigned xor, unsigned and);
unsigned long long najveca(unsigned int A[N], unsigned int B[N], int N);

int main() {
  char ulazni_buffer[1024];
  fgets(ulazni_buffer, sizeof(ulazni_buffer), stdin);
  sscanf(ulazni_buffer, "%i", &N);
  unsigned int A[N], B[N];

  fgets(ulazni_buffer, sizeof(ulazni_buffer), stdin);

  char *broj = strtok(ulazni_buffer, " ");
  int i;
  for (i = 0; i < N && broj != NULL; i++) {
    A[i] = atoi(broj);
    broj = strtok(NULL, " "); // null da bi nastavili od isto mesto
  }

  fgets(ulazni_buffer, sizeof(ulazni_buffer), stdin);
  broj = strtok(ulazni_buffer, " ");

  for (i = 0; i < N && broj != NULL; i++) {
    B[i] = atoi(broj);
    broj = strtok(NULL, " "); // null da bi nastavili od isto mesto
  }
  // for (int i = 0; i < N; i++) {
  //   printf("%i\n", A[i]);
  // }

  // for (int i = 0; i < N; i++) {
  //   printf("%i\n", B[i]);
  // }
  // printf("%llu", vrednost_podniza(2, 3, A, B, 0));
  // printf("%llu", (long long unsigned)(A[1] ^ A[2]) * (B[1] & B[2]));
  // 2-3, znaci nadji najveci podniz pa oduzmi 1 od oba indeksa

  // printf("%llu", rekurzivno(N/2, N/2 +1, A, B, A[N/2]^A[N/2 + 1],
  // B[N/2]&B[N/2 + 1], N));

  printf("%llu", iterativno(0, 0, A, B, N));
  return 0;
}

/*unsigned long long najveca(unsigned int A[N], unsigned int B[N], int N){
  int i, j;
  long long unsigned t_max, t_vrednost;
  unsigned int and, xor;
  xor = A[0]^A[1];
  and = B[0]&B[1];
  t_max = xor*and;

  for( i = 1; i<N-1; i++)
    for( j = i+1; j<N; j++){
      t_vrednost = podniz(i, j, A, B, xor, and);
      if(t_vrednost > t_max) t_max = t_vrednost;

    }
  return t_max;
}*/

unsigned long long rekurzivno(int L, int R, unsigned int A[N],
                              unsigned int B[N], unsigned int xor,
                              unsigned int and, int N) {
  unsigned int levo, desno, trenutno;

  levo = 0;
  desno = 0;

  trenutno = xor*and;
  if (L > 0)
    levo = rekurzivno(L - 1, R, A, B, xor, and,
                      N); // krece od sredinu prema levi kraj
  if (R < N - 1)
    desno = rekurzivno(L, R + 1, A, B, xor, and,
                       N); // krece od sredinu prema desni kraj
}

unsigned long long podniz(int L, int R, unsigned A[N], unsigned B[N],
                          unsigned xor, unsigned and) {}

/*unsigned long long vrednost_podniza(int L, int R, unsigned int A[N], unsigned
int B[N], unsigned int prosli_and) { L-- R--; int xor = A[L]; int and = B[L];

  int i;
  for (i = L + 1; i <= R; i++) {
    xor ^= A[i];
    and &= B[i];
  }
  return xor*and;
}*/
