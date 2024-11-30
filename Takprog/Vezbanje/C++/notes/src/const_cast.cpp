// C++ program to illustrate the const_cast
#include <iostream>
using namespace std;

int main() {

  const int a = 5;
  int *nonConstPtr = const_cast<int *>(&a);

  *nonConstPtr = 13;
  cout << "Modified number: " << *nonConstPtr;

  return 0;
}
