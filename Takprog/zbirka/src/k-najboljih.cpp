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
        std::vector<uint32_t>> pq;
    uint32_t n, k, i;

    std::cin >> n;
    std::cin >> k;
    for(i = 0; i < n; ++i){
        uint32_t pom;
        std::cin >> pom;
        pq.push(pom);
    }

    n = 0;
    for(i = 0; i < k; ++i){
        n += pq.top();
        pq.pop();
    }
    std::cout << n;
}
