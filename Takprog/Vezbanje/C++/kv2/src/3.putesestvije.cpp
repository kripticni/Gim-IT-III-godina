#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<double> vd;
typedef vector<bool> vb;
typedef vector<char> vc;
typedef vector<string> vs;
typedef vector<pi> vp;
typedef vector<pl> vpl;

// brzo sortira 3 elementa
void f(int &a, int &b, int &c) {
  if (a == min(min(b, c), a)) {
    if (b > c)
      swap(b, c);
  } else if (b == min(b, c)) {
    swap(a, b);
    if (b > c)
      swap(b, c);
  } else {
    swap(a, c);
    if (b > c)
      swap(b, c);
  }
}

// sortira 2 elementa
void f(int &a, int &b) {
  if (a > b)
    swap(a, b);
}

struct tr {
  int a;
  int b;
  int c;

  bool operator<(const tr &other) const {
    if (a != other.a)
      return a < other.a;
    if (b != other.b)
      return b < other.b;
    return c < other.c;
    // vrati poredjenje prva dva razlicita, ili poredjenje c
  }
};

tr ff(int a, int b, int c) {
  f(a, b, c);
  return tr{a, b, c}; // vrati novi sortiran konstruisan element
}

map<tr, int> m;
map<tr, pi> e;
map<pi, int> zau;
const int maxn = 2e5 + 10;
vi g[maxn], vis(maxn);

vi sol;

void dfs(int x) {
  sol.push_back(x);
  vis[x] = 1;

  for (int i : g[x]) {
    if (vis[i])
      continue;
    dfs(i);
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cerr.tie(nullptr);

  int n;
  cin >> n;

  vector<tr> t = {{1, 2, 3}}; // incializuje tacku 4
  m[tr{1, 2, 3}] = 4;         // mapira da je 1,2,3 za tacku 4
  e[tr{1, 2, 3}] = {1, 2};    // da je 1,2,3 par od 1,2?

  for (int i = 5; i <= n; ++i) { // krecemo od 5 jer znamo 1 2 3 4
    int a, b, c;
    cin >> a >> b >> c;

    f(a, b, c);

    t.push_back({a, b, c}); // mogli su da urade emplace_back sa ff
    m[t.back()] = i;        // ovaj element se mapira kao tacka i
  }

  set<pi> s; // ima da skontam sve ovo neki drugi put
  s.insert({1, 2});
  s.insert({2, 3});
  s.insert({1, 3});
  for (int i = 4; i <= n; ++i) {
    auto p = t[i - 4];
    auto h = e[p];

    int u = h.first, v = h.second, x = i;
    s.erase({u, v});
    s.insert({u, x});
    s.insert({v, x});

    int w = p.c + p.a + p.b - u - v;
    if (!m[ff(u, v, x)]) {

      auto q = ff(u, w, x);
      e[q] = {u, x};

      auto k = ff(v, w, x);
      e[k] = {v, x};
    } else if (!m[ff(u, w, x)]) {
      auto q = ff(u, v, x);
      e[q] = {u, x};

      auto k = ff(v, w, x);
      e[k] = {v, x};
    } else {
      auto q = ff(u, v, x);
      e[q] = {v, x};

      auto k = ff(u, w, x);
      e[k] = {u, x};
    }
  }

  for (pi p : s) {
    g[p.first].push_back(p.second);
    g[p.second].push_back(p.first);
  }
  dfs(1);

  for (int x : sol)
    cout << x << ' ';
  cout << "1\n";
}
