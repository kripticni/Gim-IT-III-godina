#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tacka {
  long long int x; // mora da bude signed zbog formule
  long long int y;
} Tacka;

typedef struct Point Point;

int N;

long long int minimalno(long long int x, long long int y) {
  return (x < y ? x : y);
}

long long int maksimum(long long int x, long long int y) {
  return (x > y ? x : y);
}

bool u_mnogouglu(Tacka tacka, Tacka mnogougao[N]) {
  double x = (double)tacka.x, y = (double)tacka.y;
  bool zastava = false;

  Tacka t1 = mnogougao[0], t2;

  for (int i = 1; i <= N; i++) {
    t2 = mnogougao[i % N];
    if (y > (double)minimalno(t1.y, t2.y)) {
      if (y <= (double)maksimum(t1.y, t2.y)) {
        if (x <= (double)maksimum(t1.x, t2.x)) {
          double x_presek = (y - (double)t1.y) * (double)(t2.x - t1.x) /
                            (double)((t2.y - t1.y) + t1.x);

          if (t1.x == t2.x || x <= x_presek) {
            zastava = !zastava;
          }
        }
      }
    }

    t1 = t2;
  }

  return zastava;
}

#define llu long long int
struct Point {
  llu x, y;
};

unsigned long long povrs_mnogougla(Point *koordinate, int n) {
  long long int povratna = 0;

  // gausova formula, radjeno ove godine u skoli
  int j = n - 1, i;
  for (i = 0; i < n; i++) {
    povratna += (koordinate[j].x + koordinate[i].x) *
                (koordinate[j].y - koordinate[i].y);
    j = i;
  }

  return llabs(povratna / 2);
}

// izvor:
// https://www.geeksforgeeks.org/convex-hull-algorithm-in-c/#3-convex-hull-using-graham-scan

// Comparison function to sort points lexicographically
int compare(const void *a, const void *b) {
  struct Point *p1 = (struct Point *)a;
  struct Point *p2 = (struct Point *)b;
  if (p1->x != p2->x)
    return (p1->x < p2->x) ? -1 : 1;
  return (p1->y < p2->y) ? -1 : 1;
}

// Cross product of two vectors OA and OB
// returns positive for counterclockwise
// turn and negative for clockwise turn
llu cross_product(struct Point O, struct Point A, struct Point B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counterclockwise order
struct Point *convex_hull(struct Point *A, int n, int *hull_size) {
  if (n <= 3) {
    *hull_size = n;
    return A;
  }

  struct Point *ans = (struct Point *)malloc(2 * n * sizeof(struct Point));
  int k = 0;

  // Sort points lexicographically
  qsort(A, n, sizeof(struct Point), compare);

  // Build lower hull
  for (int i = 0; i < n; ++i) {
    while (k >= 2 && cross_product(ans[k - 2], ans[k - 1], A[i]) <= 0)
      k--;
    ans[k++] = A[i];
  }

  // Build upper hull
  for (int i = n - 1, t = k + 1; i > 0; --i) {
    while (k >= t && cross_product(ans[k - 2], ans[k - 1], A[i - 1]) <= 0)
      k--;
    ans[k++] = A[i - 1];
  }

  *hull_size = k - 1;
  return ans;
}

int main() {
  unsigned long long povrsina;
  scanf("%i", &N);
  struct Point unos[N];
  int i;
  for (i = 0; i < N; i++)
    scanf("%lli%lli", &unos[i].x, &unos[i].y);

  // printf("%llu", povrs_mnogougla(unos));
  //
  // Tacka cetvrta = {12, 14};
  // printf("%i", u_mnogouglu(cetvrta, unos));

  int hull_size;
  long long unsigned min = 0xffffffff, tren;
  struct Point prenos[N];
  int j = 0;
  int z = 0;
  for (i = 0; i < N; i++) {
    j = 0;
    z = 0;
    while (j < i) {
      prenos[z] = unos[j];
      j++;
      z++;
    }
    j++;
    while (j < N) {
      prenos[z] = unos[j];
      j++;
      z++;
    }

    if (N - 1 > 2) {
      struct Point *ans = convex_hull(prenos, N - 1, &hull_size);
      if (hull_size > 2)
        tren = povrs_mnogougla(ans, hull_size);
    }
    // printf("\n%lli\n", tren);
    if (tren < min)
      min = tren;
  }
  printf("%lli", min);

  return 0;
}
