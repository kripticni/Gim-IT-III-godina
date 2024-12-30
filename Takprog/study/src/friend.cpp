#include <iostream>
using namespace std;
class Largest {
  int a, b, m;

public:
  void set_data();
  friend void find_max(Largest);
};

void Largest::set_data() {
  cout << "Enter the first number : ";
  cin >> a;
  cout << "\nEnter the second number : ";
  cin >> b;
}

void find_max(Largest t) {
  if (t.a > t.b)
    t.m = t.a;
  else
    t.m = t.b;

  cout << "\nLargest number is " << t.m;
}

int main() {
  Largest l;
  l.set_data();
  find_max(l);
  return 0;
}
