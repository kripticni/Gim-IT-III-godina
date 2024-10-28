#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int main_geometrijski() {
  int x[3];
  int y[3];
  int i;

  float det, p;
  for (i = (int)'A'; i < (int)'D'; i++) {
    printf("Unesite %cx, onda %cy: ", i, i);
    scanf("%i", &x[i - 'A']);
    scanf("%i", &y[i - 'A']);
  }
  det = (x[1] - x[0]) * (y[2] - y[0]) - (y[1] - y[0]) * (x[2] - x[0]);

  p = fabs(det) / 2.0;
  printf("Povrsina je %f\n", p);
  if (det > 0)
    printf("Pozitivna");
  else if (det == 0)
    printf("Kolinearna");
  else
    printf("Negativna");
  return 0;
}
