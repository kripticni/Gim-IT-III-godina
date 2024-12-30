#include <iostream>
#include <set>

using namespace std;

int main() {
  int n;
  cin >> n;
  multiset<int> a;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    a.insert(x);
  }
  for (int x : a)
    cout << x << '\n';
  return 0;
}
