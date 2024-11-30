#include <iostream>
#include <mutex> //for locks
#include <thread>

using namespace std;

thread_local int value = 10;
mutex mtx; // for syncing threads

int main() {
  thread th1([]() {
    value += 18;
    lock_guard<mutex> lock(mtx);
    cout << "Thread 1 value: " << value << '\n';
  });

  thread th2([]() {
    value += 7;
    lock_guard<mutex> lock(mtx);
    cout << "Thread 2 value: " << value << '\n';
  });

  thread th3([]() {
    value += 13;
    lock_guard<mutex> lock(mtx);
    cout << "Thread 3 value: " << value << '\n';
  });

  th1.join();
  th2.join();
  th3.join();

  cout << "Main thread value: " << value << '\n';
  return 0;
}
