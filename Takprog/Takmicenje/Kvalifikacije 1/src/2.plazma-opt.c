#include <stdio.h>
#include <stdlib.h>

int main() {
  long long int N, Q;
  scanf("%lli %lli", &N, &Q);
  // printf("%i %i\n", N, Q);
  fflush(stdin);

  long long int i;
  long long int d[N], p[N];
  for (i = 0; i < N; i++)
    scanf("%lli %lli", &d[i], &p[i]);

  // for (i = 0; i < N; i++)
  //   printf("%i %i\n", d[i], p[i]);

  long long int k[Q];
  for (i = 0; i < Q; i++)
    scanf("%lli", &k[i]);

  // for (i = 0; i < Q; i++)
  //   printf("%i\n", k[i]);

  /*
   i oznacava interaciju kad je plazma pronadjena, a d[i] koji je tad dan
   p[i] je broj pakovanja na d[i]-ti dan
   svakog dana se gubi jedno pakovanje plazme, znaci zadnji d[i] je broj
   izgubljene plazme

   pitanja samo daju dan, i pitaju: zbir(p[ od 0 do (k[j] < d[i]]) - k[i]
  */

  long long int j, z, suma, pojedeno, pronalazak;

  for (j = 0; j < Q; j++) {
    suma = 0;
    pojedeno = 0;
    pronalazak = 0;
    for (z = d[pronalazak]; z <= k[j];) {
      while (z >= d[pronalazak] && pronalazak < N) {
        suma += p[pronalazak];
        pronalazak++;
      }

      if (suma > 0) {
        if (z + suma < k[j]) {
          z += suma;
          pojedeno += suma;
          suma = 0;
        } else {
          pojedeno += k[j] - z + 1;
          goto ispis;
        }
      } else {
        if (pronalazak < N) {
          if (d[pronalazak] < k[j])
            z = d[pronalazak];
          else
            z++;
        } else
          goto ispis;
      }
    }
  ispis:
    printf("%lli\n", pojedeno);
  }

  return 0;
}
