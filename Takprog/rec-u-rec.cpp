#include <bits/stdc++.h>
#include <cstdint>
#include <cstring>

int main() noexcept {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string a;
    std::string b;

    std::cin >> a;
    std::cin >> b;

    uint32_t n, m, i, j;
    n = a.size();
    m = b.size();
    j = 0;
    for(i = 0; i < n && j < m; ++i){
        if(b[j] == a[i])
            ++j;
    }

    if(j == m)
        std::cout << "da";
    else
        std::cout << "ne";
}
