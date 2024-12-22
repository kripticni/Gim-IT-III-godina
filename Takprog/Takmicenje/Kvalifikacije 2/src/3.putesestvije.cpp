#include <algorithm>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <vector>

constexpr const uint32_t MAX_N = 200001;
// ne zelim da imam sub instrukciju
// za svaki unos
// pa onda da imam jedan add
// za svaki izlaz
std::vector<std::vector<uint32_t>> graf;
std::vector<uint32_t> staza;
std::bitset<MAX_N> stanja;
uint32_t n;

void sastavi() noexcept {
  uint32_t i, a, b, c;
  graf.resize(n + 1);

  graf[1] = {2, 3, 4};
  graf[2] = {1, 3, 4};
  graf[3] = {1, 2, 4};
  graf[4] = {1, 2, 3};

  for (i = 5; i < n + 1; ++i) {
    std::cin >> a >> b >> c;

    graf[i].emplace_back(a); // malo brze
    graf[i].emplace_back(b);
    graf[i].emplace_back(c);
    graf[a].emplace_back(i);
    graf[b].emplace_back(i);
    graf[c].emplace_back(i);
  }
}

[[gnu::hot]] [[gnu::noinline]]
static bool backtrack(uint32_t tr, uint32_t br) noexcept {
  if (br == n) {
    // odjednom se oseca lepo da se pise u cpp
    if (std::find(graf[tr].begin(), graf[tr].end(), 1) != graf[tr].end()) {
      [[unlikely]] staza.emplace_back(1);
      return true;
    }
    return false;
  }

  for (auto sused : graf[tr]) {
    if (!stanja.test(sused)) {
      stanja.set(sused);
      staza.emplace_back(sused);

      if (backtrack(sused, br + 1))
        return true;

      stanja.reset(sused);
      staza.pop_back();
    }
  }

  return false;
}

int main() noexcept {
  std::cin.tie(NULL);
  std::ios::sync_with_stdio(false);

  std::cin >> n;
  // std::cout << sizeof(stanja);

  // for (i = 5; i < n; ++i) //da ne bi oduzimali
  //   std::cin >> graf[i][0] >> graf[i][1] >> graf[i][2];

  sastavi();
  // sad kad bi hteo da uradim memset
  // bi mnogo vise voleo da sam koristio niz
  stanja.reset();
  stanja.set(1);
  staza.emplace_back(1);

  if (!backtrack(1, 1)) {
    std::cout << "-1";
  } else {
    for (auto &itr : staza)
      std::cout << itr << ' ';
  }

  /*
  for (i = 0; i < n; ++i)
    std::cout << graf[i][0] << ' ' << graf[i][1] << ' ' << graf[i][2];
  */
}
