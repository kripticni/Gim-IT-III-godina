#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, int32_t> banka;

[[gnu::hot]]
static uint32_t upit(int32_t &num) noexcept {
  return std::count_if(banka.begin(), banka.end(), [&](auto &korisnik) -> bool {
    return korisnik.second == num;
  });
}

[[gnu::hot]]
static void ime(std::string &str, int32_t &num) noexcept {
  auto korisnik = banka.find(str);
  if (korisnik != banka.end())
    korisnik->second += num;
  else
    banka.emplace(str, num);
}

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  uint32_t n, k;
  std::cin >> n >> k;

  banka.reserve(k);

  for (uint32_t i = 0; i < n; ++i) {
    std::string funt;
    int32_t arg;
    std::cin >> funt >> arg;
    if (funt == "upit")
      std::cout << upit(arg) << '\n';
    else
      ime(funt, arg);
  }
}
