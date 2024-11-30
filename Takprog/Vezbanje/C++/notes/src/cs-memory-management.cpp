#include <cstring>
#include <iostream>
using namespace std;

int main() {
  int num = 5;
  float *ptr;

  ptr = new float[num];
  // so this new float[num]; creates an array of size num, and returns a pointer

  for (int i = 0; i < num; ++i) // the ++i optimization
    *(ptr + i) = i;

  for (int i = 0; i < num; ++i) // the ++i optimization
    cout << i << " is " << *(ptr + i) << ':';

  cout << endl;

  for (int i = 0; i < num; ++i)           // the ++i optimization
    cout << i << " is " << ptr[i] << ':'; // checking if its the same as in C

  delete[] ptr; // this frees the memory
  return 0;
}
