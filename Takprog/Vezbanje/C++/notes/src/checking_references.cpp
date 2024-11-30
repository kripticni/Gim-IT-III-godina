#include <iostream>
using namespace std;

void function(int &b) {
  cout << &b;
  return;
}

int main() {
  int a;
  a = 5;
  cout << &a << endl;
  function(a);
  // so this actually does use the same address in the function
  // which id like to assume is amazing for performance, in cases where
  // there is no need for cache locality
}
