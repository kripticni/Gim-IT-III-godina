#include <iostream>
#include <vector>
#include <stack>
#include <cstdint>
#include <algorithm>

int main() noexcept
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<int32_t> niz;
    std::stack<int32_t> stek;
    uint16_t n, i;

    std::cin >> n;
    niz.reserve(n);
    for(i = 0; i < n; ++i){
        int32_t h;
        std::cin >> h;
        niz.emplace_back(h);
    }

    std::sort(niz.begin(), niz.end());
    for(i = 0; i < n/2; ++i){
        stek.push(niz[i]);
        stek.push(niz[n - i - 1]);
    }

    if(n&1)
        stek.push(niz[n/2]);

    int32_t pom;
    for(i = 0; i < n; ++i){
        pom = stek.top();
        stek.pop();
        std::cout << pom << ' ';
    }
}
