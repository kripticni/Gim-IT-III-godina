#include <cstdlib>
#include <iostream>
#include <pthread.h>

// from geeksforgeeks, there has already been an error
// in their documentation here, the function was printing
// address of i instead of process id, because thats what they passed
// i was able to figure it out regardless

using namespace std;

#define NUM_THREADS                                                            \
  4 - 1 // num of logical cores/threads on my system
        // also -1 because of one thread used for main?

void *PrintHello(void *threadid) {
  int tid;
  tid = *(int *)threadid;

  // Print the thread ID
  cout << "Hello World! Value of i, " << tid << endl;

  pthread_exit(NULL);
}

int main() {
  pthread_t threads[NUM_THREADS]; // this makes threads, as a static array
  int rc;
  int i;

  for (i = 0; i < NUM_THREADS; i++) {
    rc = pthread_create(&threads[i], NULL, PrintHello, (void *)&i);
    cout << "main() : creating thread, " << threads[i] << endl;
    // pthread create returns 0 on sucessful thread create, and ENOMEM on memory
    // allocation failure If thread is not created
    if (rc) {
      cout << "Error:unable to"
           << " create thread, " << rc << endl;

      exit(-1);
    }
  }

  pthread_exit(NULL);
}
