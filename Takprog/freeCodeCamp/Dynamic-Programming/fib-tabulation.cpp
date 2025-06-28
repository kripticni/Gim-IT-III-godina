#include <iostream>
using namespace std;
int fib(int n){
  if(n <= 0) return 0;
  if(n == 1 || n == 2) return 1;

  int a = 1, b = 1, s = 0, i;
  for(i = 3; i < n; ++i){
    s = a + b; 
    b = a;
    a = s;
  }
  return s;
}

int main(){
  cout << fib(3) << '\n'; 
  cout << fib(4) << '\n'; 
  cout << fib(5) << '\n'; 
  cout << fib(6) << '\n'; 
  cout << fib(7) << '\n'; 
  cout << fib(8) << '\n'; 
  cout << fib(9) << '\n'; 
}
