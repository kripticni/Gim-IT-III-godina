#include <bits/stdc++.h>
using namespace std; // this makes me not need to type std::

int main() {
  auto integer = 3; // automatically determines the type
  auto a_bool = false;
  auto a_float = 3.14; // double?
  auto ptr = &integer;

  cout << a_bool << "\n";
  cout << typeid(a_bool).name() << "\n"; // this types the type character
  cout << typeid(integer).name()
       << endl; // same as new line, so this is pipelining basically
  return 0;
}
