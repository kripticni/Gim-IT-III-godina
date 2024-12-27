#include <bits/stdc++.h>
#define maxn 12000

using namespace std;

int n, m;
int a[maxn];
int dp[maxn];
int ans[maxn];

deque<pair<int, int>> dq;

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  cin >> n >> m;
  // M braca
  // N slike
  for (int i = 0; i < n; i++)
    cin >> a[i];

  for (int cleft = 0; cleft < m; cleft++) {
    int l = cleft; // duzina svakog prozora, na osnovu brata
    for (int i = 0; i + l < n; i++)
      dp[i] = max(a[i], a[i + l]);
    // cuvamo maksimum za svaki prozor duzine L
    // od pocetka do kraja duzine slika

    // sa ova dva for loopa garantujemo da
    // ima da prodjemo svaki podniz
    // od broja brata do kraja niza jer
    // se samo ti podnizi racunaju za
    // datog brata

    while (l + m < n) { // za svaki postojeci opseg
      dq.clear();
      for (int i = n - 1 - l; i >= 0;
           i--) { // i krece od zadnjeg postojeceg opsega slika, suprotno od max
                  // for loopa
        while (!dq.empty() && dq.front().first >= dp[i])
          dq.pop_front();           // dok su svi iste max vrednosti
        dq.emplace_front(dp[i], i); // vrati tako da postoji samo jedna vrednost
                                    // i sa istim max vrednostima u queue
        if (dq.back().second == i + m)
          dq.pop_back(); // ako su elementi tacno udaljeni za jedan opseg,
                         // izbrisemo levi element
        dp[i] = dq.back().first; // onda je konacna vrednost prvi prozor koji
                                 // nije udaljen za m
      }
      l += m; // povecamo opseg za m
      for (int i = 0; i + l < n; i++)
        dp[i] = max(a[i] + dp[i + 1], a[i + l] + dp[i]);
      // uzimamo max od levog + celog levog podstabla
      // ili desnog + celog desnog podstabla
    }
    // kad smo zavrsili prekomputaciju

    ans[n - l] = 1e9; // za edge case
    // odgovori od 0 do trenutnog zadnjeg opsega su:
    for (int i = 0; i + l < n; i++)
      ans[n - l] = min(ans[n - l], dp[i]);
  }
  for (int i = 1; i <= m; i++)
    cout << ans[i] << " ";
  return 0;
}
