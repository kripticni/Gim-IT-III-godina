#include <cstdint>
#include <iostream>

// S obzirom da ce ovaj kod biti pregledan
// od strane petlje, i verovatno biti uporedjen sa
// mojim proslim krugom, samo bih hteo da naglasim
// da ja jesam naucio c++ i dobar broj algoritama
// kompajlerskih optimizacija i arhitekture racunara
// pre ovog kruga, dobar deo toga je dokumentovan na
// takodje cu primenjivati znanje iz asemblera
// https://github.com/kripticni
//
// Takodje sve ostale komentare koje bih inace napisao
// u svom kodu cu da izbacim jer znam da mogu i drugi
// takmicari da procitaju moja resenja
//
// formatirano sa clang-format

int main() noexcept {
  std::cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  // 1000000000000000000
  // 4294967295
  // 18446744073709552000

  uint64_t a, b;
  std::cin >> a;
  std::cin >> b;

  // max medijana je uvek veci od brojava a i b, bez obzira na C
  // uint64_t medijana;
  // medijana = (a > b) ? a : b;

  // (a + b + c)/3 <= a + b + c - min(a,b,c) - max(a,b,c)
  // prosek = medijana
  // =)
  // p = (a+b+c)/3
  // 3p = (a+b+c)
  // 3p - a - b = c
  // 3m - a - b = c

  // uint64_t c = 3 * medijana - a - b;
  // std::cout << c;
  std::cout << 3 * ((a > b) ? a : b) - a - b;
}
// p = (a + b + c)/3
// p = (a + c + (a + b + c - min(a,b,c) - max(a,b,c))/3
// p = (2a + 2c + b - min(a,b,c) - max(a,b,c))/3
// 3p = 2a + 2c + b - min(a,b,c) - max(a,b,c)
// 3p - a - c = a + b + c - min(a,b,c) - max(a,b,c)
// c = m + a + c - 3p
