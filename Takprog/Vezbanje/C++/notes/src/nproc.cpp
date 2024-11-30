#include <bits/stdc++.h>
#include <thread>

int main() {
  const auto nproc = std::thread::hardware_concurrency();
  std::cout << nproc;
}
