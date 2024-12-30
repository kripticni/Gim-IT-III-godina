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
    int l = cleft; // za svakog brata po jedan ciklus
    for (int i = 0; i + l < n; i++)
      dp[i] = max(a[i], a[i + l]);
    // cuvamo maksimum za svaki moguci prozor
    // sa 0 + broj brata, do kraja slika

    while (l + m < n) {
      // dok postoji sledeci ciklus
      // jedan ciklus je M jer toliko
      // poteza treba dok se vratimo
      // na brata L
      dq.clear();
      for (int i = n - l - 1; i >= 0; i--) {
        // idemo unazad kroz niz dp[i]
        while (!dq.empty() && dq.front().first >= dp[i])
          dq.pop_front();           // dok su iste max vrednosti brisemo
        dq.emplace_front(dp[i], i); // cuvamo samo onaj sa najmanjom vrednoscu i

        // ako su elementi tacno udaljeni za jedan ciklus, to je ustvari isti
        // ciklus, ali sa vecom vrednoscu i, a mi brisemo jer trazimo najmanju
        if (dq.back().second == i + m)
          dq.pop_back();
        dp[i] = dq.back().first; // onda je konacna vrednost prvi prozor koji
                                 // nije udaljen za m, sa najmanjom vrednoscu i
      }
      l += m; // povecamo l za ciklus
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
    // za brata l, ovo racuna vrednosti od 0, n-l-m
    // tako da ovo racuna minimume za svaki index iz niza slika
  }
  for (int i = 1; i <= m; i++)
    cout << ans[i] << " ";
  return 0;
}
