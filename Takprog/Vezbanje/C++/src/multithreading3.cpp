#include <iostream>
#include <thread>
#include <vector>

using namespace std;

#define NUM_THREADS (4 - 1)

void printHello(int threadid) {
  cout << "Hello World! Value of i, " << threadid << endl;
}

int main() {
  vector<thread> threads;

  for (int i = 0; i < NUM_THREADS; i++) {
    threads.emplace_back(printHello, i);
    cout << "main() : creating thread, ID = " << i << endl;
  }

  for (auto &t : threads) {
    t.join();
  }

  cout << "All threads completed execution." << endl;

  return 0;
}
