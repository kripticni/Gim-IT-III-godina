#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <map>

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);

  std::map<char, int16_t> count;
  std::string buff;

  std::getline(std::cin, buff);
  for (char &c : buff)
    c = std::tolower(c);

  for (char &c : buff)
    ++count[c];

  std::getline(std::cin, buff);

  for (char &c : buff)
    c = std::tolower(c);

  for (char &c : buff)
    --count[c];

  count.erase(' ');
  for (auto itr = count.begin(); itr != count.end(); ++itr)
    if (itr->second != 0) {
      printf("ne");
      return 0;
    }
  printf("da");
}
