#include <iostream>
#include <vector>
using namespace std;
int main() {
  // Declaring a vector
  vector<int> v = {1, 2, 3};

  // Declaring an iterator
  vector<int>::iterator i;

  int j;

  // Inserting element using iterators
  for (i = v.begin(); i != v.end(); ++i) {
    if (i == v.begin()) {
      i = v.insert(i, 5);
      // inserting 5 at the beginning of v
    }
  }

  // v contains 5 1 2 3

  // Deleting a element using iterators
  for (i = v.begin(); i != v.end(); ++i) {
    if (i == v.begin() + 1) {
      i = v.erase(i);
      // i now points to the element after the
      // deleted element
    }
  }

  // v contains 5 2 3

  // Accessing the elements using iterators
  for (i = v.begin(); i != v.end(); ++i) {
    cout << *i << " ";
  }

  return 0;
}
