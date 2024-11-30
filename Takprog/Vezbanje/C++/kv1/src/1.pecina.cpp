#include <stdio.h>

int main() {
  int N, L;
  scanf("%i %i", &N, &L);

  register int i;
  int cur;
  for (i = 1; i <= N; ++i) {
    scanf("%i", &cur);
    if (L >= cur) {
      printf("%i", i);
      return 0;
    }
  }
  printf("-1");
  return 0;
}
