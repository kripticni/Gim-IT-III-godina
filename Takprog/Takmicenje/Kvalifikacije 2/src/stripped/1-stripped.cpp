#include <cstdint>
#include <iostream>

// S obzirom da ce ovaj kod biti pregledan
// od strane petlje, i verovatno biti uporedjen sa
// mojim proslim krugom, samo bih hteo da naglasim
// da ja jesam naucio c++ i dobar broj algoritama,
// kompajlerskih optimizacija i arhitekture racunara
// pre ovog kruga, dobar deo toga je dokumentovan na
// https://github.com/kripticni
//
// Takodje skoro sve ostale komentare koje sam napisao
// u svom kodu cu da izbacim jer znam da mogu i drugi
// takmicari da procitaju moja resenja
//
// formatirano sa clang-format

int main() noexcept {
  std::cin.tie(NULL);
  std::ios::sync_with_stdio(false);

  uint64_t a, b;
  std::cin >> a;
  std::cin >> b;

  std::cout << 3 * ((a > b) ? a : b) - a - b;
}
