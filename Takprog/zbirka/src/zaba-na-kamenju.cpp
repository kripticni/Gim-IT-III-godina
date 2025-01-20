#include <iostream>
#include <vector>
#include <memory>

int main() noexcept
{
    std::vector<uint64_t> niz;
    uint64_t r;
    uint16_t n, i, j, br;
    bool flag;
    std::cin >> n;

    niz.reserve(n);
    for(i = 0; i < n; ++i)
        std::cin >> niz[i];

    std::cin >> r;

    br = 0;
    i = 0;
    j = 1;
    while(i < n - 1){
        flag = true;
        while(niz[i] + r >= niz[j] && j < n){
            ++j;
            flag = false;
        }
        if(flag){
            std::cout << "-1";
            return 0;
        }
        ++br;
        i = j - 1;
    }
    std::cout << br;
}
/*
5
0 3 8 14 16
10
*/
