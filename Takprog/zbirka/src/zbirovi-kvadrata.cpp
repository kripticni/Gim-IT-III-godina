#include <iostream>
#include <memory>
#include <cstdint>
#include <queue>
#include <algorithm>

/*
struct cmp {
    bool operator()(const std::tuple<uint64_t, uint64_t, uint64_t>& a,
                    const std::tuple<uint64_t, uint64_t, uint64_t>& b) const {
        return std::get<2>(a) > std::get<2>(b);
    }
};
*/ 
// this makes an issue because it doesnt check the values for a and b if p is equal

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::priority_queue<std::tuple<uint64_t, uint64_t, uint64_t>,
    std::vector<std::tuple<uint64_t, uint64_t, uint64_t>>,
    std::greater<std::tuple<uint64_t, uint64_t, uint64_t>>> pq;
  uint64_t p;
  uint64_t n, a, b;
  int64_t k, i;

  std::cin >> n >> k;

  for(a = 0; a <= n; ++a)
    pq.emplace(a*a*2,a,a);

  for(i = 0; i < k; ++i){
    std::tie(p,a,b) = pq.top();
    //std::cout << a << ' ' << b << ' ' << p << '\n';
    pq.pop();

    if(b < n){
      ++b;
      pq.emplace(a*a + b*b, a,b);
    } 
    /*else {
      ++b;
      pq.emplace(a,b,a*a + b*b);
    }
    */
  }

  std::tie(p, a, b) = pq.top();
  std::cout << a << ' ' << b << ' ' << p;
}
