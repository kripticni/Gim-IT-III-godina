#include <iostream>
#include <memory>
#include <cstdint>
#include <queue>

int main() noexcept {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cerr.tie(nullptr);

    std::priority_queue<uint32_t,
        std::vector<uint32_t>,
        std::greater<uint32_t>> pq;
    uint32_t n, i;

    std::cin >> n;
    for(i = 0; i < n; ++i){
        uint32_t pom;
        std::cin >> pom;
        pq.push(pom);
    }

    while(!pq.empty()){
        std::cout << pq.top() << '\n';
        pq.pop();
    }
}
