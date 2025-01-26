#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>

int main() noexcept {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    uint32_t n;
    std::cin >> n;
    std::vector<std::pair<uint32_t, uint32_t>> arr(n);

    for (uint32_t i = 0; i < n; ++i) {
        uint16_t h, m;
        uint32_t start, end;

        std::cin >> h >> m;
        start = h * 60 + m;

        std::cin >> h >> m;
        end = h * 60 + m;

        arr.emplace_back(start, end);
    }

    std::sort(arr.begin(), arr.end());
    std::priority_queue<uint32_t, std::vector<uint32_t>, std::greater<uint32_t>> pq;

    for (const auto& interval : arr) {
        if (!pq.empty() && pq.top() <= interval.first)
            pq.pop();
        pq.push(interval.second);
    }

    std::cout << pq.size();
    return 0;
}
