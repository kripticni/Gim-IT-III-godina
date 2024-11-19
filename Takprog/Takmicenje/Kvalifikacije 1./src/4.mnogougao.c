#include <stdio.h>
#include <stdlib.h>

struct Point {
  long long int x, y;
};

unsigned long long povrs_mnogougla(struct Point *koordinate, int N) {
  long long int povratna = 0;

  // gausova formula, radjeno ove godine u skoli
  int j = N - 1, i;
  for (i = 0; i < N; i++) {
    povratna += (koordinate[j].x + koordinate[i].x) *
                (koordinate[j].y - koordinate[i].y);
    j = i;
  }

  return llabs(povratna / 2);
}

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
long long int cross_product(struct Point O, struct Point A, struct Point B) {
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
  int N;
  unsigned long long povrsina;
  scanf("%i", &N);
  struct Point unos[N];
  struct Point odvojeno[N];

  int i;
  for (i = 0; i < N; i++)
    scanf("%lli%lli", &unos[i].x, &unos[i].y);

  int hull_size;
  long long unsigned min = 0xffffffffffffffff, tren;
  struct Point prenos[N - 1];

  for (i = 0; i < N; i++) {
    int y = 0;
    for (int x = 0; x < N; x++) {
      if (x != i) {
        prenos[y] = unos[x];
        y++;
      }
    }

    if (N - 1 > 2) {
      struct Point *ans = convex_hull(prenos, N - 1, &hull_size);
      if (hull_size > 2)
        tren = povrs_mnogougla(ans, hull_size);
    }

    if (tren < min)
      min = tren;
  }

  printf("%llu", min);

  return 0;
}
