#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
  map<string, int> mp;

  mp["one"] = 1;
  mp["two"] = 2;
  mp["three"] = 3;

  map<string, int>::iterator it = mp.begin();

  while (it != mp.end()) {
    cout << "Key: " << it->first << ", Value: " << it->second << endl;
    ++it;
  }

  return 0;
}
