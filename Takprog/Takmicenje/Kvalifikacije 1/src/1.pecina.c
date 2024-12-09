#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// formatirano sa clang-formatter
int main() {
  int N, L;
  scanf("%i %i\n", &N, &L); // bez novu liniju fgets ne bi radio
  // printf("%i %i", N, L);

  char ulazni_buffer[1024];
  fflush(stdin); // ponovo, zbog fgets
  fgets(ulazni_buffer, sizeof(ulazni_buffer), stdin);

  int H[N];
  char *broj = strtok(ulazni_buffer, " ");
  int i;
  for (i = 0; i < N && broj != NULL; i++) {
    H[i] = atoi(broj);
    broj = strtok(NULL, " "); // null da bi nastavili od isto mesto
  }
  // NAPOMENA: na osnovu provere ovo bi trebalo da je dovoljno dobro za unos

  for (i = 0; i < N; i++)
    if (L >= H[i])
      break;

  if (i == N)
    printf("-1");
  else
    printf("%i", i + 1);

  return 0;
}
