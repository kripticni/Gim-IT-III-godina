#include <stdio.h>

int main() {
  long long N, Q, i, j, z, pojedeno = 0, pronalazak = 0, odgovoreno = 0,
                           suma = 0;
  scanf("%lli %lli", &N, &Q);

  long long int d[N], p[N], k[Q];

  for (i = 0; i < N; ++i)
    scanf("%lli %lli", &d[i], &p[i]);

  for (i = 0; i < Q; i++)
    scanf("%lli", &k[i]);

  i = d[0];
  /*
  while (i < k[Q - 1]) {
    while (i >= d[pronadjeno] && pronadjeno < N) {
      pojedeno += p[pronadjeno];
      i += p[pronadjeno];
      while (i >= k[odgovoreno] && odgovoreno < Q) {
        printf("%lli\n", k[odgovoreno] - i + pojedeno + 1);
        ++odgovoreno;
      }
      ++pronadjeno;
    }
    i = d[pronadjeno];
  }
  */

  for (j = 0; j < Q; j++) {
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
