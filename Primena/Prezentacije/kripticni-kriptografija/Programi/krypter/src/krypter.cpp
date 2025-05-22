#include "../lib/kryptos.hpp"
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

void printUsage(const char *progName) {
  std::cout << "Koriscenje:\n"
            << progName
            << " <sifra> <e|d|ef|df> <text> <key_or_shift_or_rotor>\n"
            << "Sifre:\n"
            << "  caesar\n"
            << "  vigenere\n"
            << "  hebern\n"
            << "Primer:\n"
            << progName << " caesar e HELLO 3\n";
}

void cmdline(int argc, char *argv[]);
void interactive();

[[gnu::noreturn]]
int main(int argc, char *argv[]) {
  // std::cout << argc << std::endl;
  //  std::ios::sync_with_stdio(false);
  //   std::cin.tie(nullptr);
  //    std::cout.tie(nullptr);
  //   std::cerr.tie(nullptr);

  if (argc == 5)
    cmdline(argc, argv);
  else
    interactive();
}

constexpr uint8_t cksum(const std::string_view &data) {
  uint8_t sum = 0;
  for (uint8_t c : data)
    sum += static_cast<unsigned char>(c);
  return sum;
}

constexpr uint8_t CKSUM_CAESAR = cksum("caesar");
constexpr uint8_t CKSUM_VIGENERE = cksum("vigenere");
constexpr uint8_t CKSUM_HEBERN = cksum("hebern");

[[gnu::noreturn]]
void cmdline(int argc, char *argv[]) {
  std::string cipher = argv[1];
  uint8_t decision = cksum(cipher);
  // std::cout << "Decided: " << (uint16_t)decision << '\n';
  // std::cout << (uint16_t)CKSUM_CAESAR;
  if (decision != CKSUM_CAESAR && decision != CKSUM_VIGENERE &&
      decision != CKSUM_HEBERN) {
    std::cerr << "Nije validna sifra.\n";
    printUsage(argv[0]);
    exit(1);
  }

  std::string action_arg = argv[2];
  if (action_arg != "e" && action_arg != "d" && action_arg != "ef" &&
      action_arg != "df") {
    std::cerr << "Nije validan izbor za enkripciju/dekripciju: " << action_arg
              << "\n";
    printUsage(argv[0]);
    exit(1);
  }

  bool action = action_arg[0] == 'e' ? true : false;
  bool isFile = action_arg[1] == 'f' ? true : false;
  constexpr bool ENC = true;
  constexpr bool DEC = false;

  std::string text;
  if (!isFile)
    std::string text = argv[3];
  else {
    std::ifstream file(argv[3]);
    if (!file) {
      std::cerr << "Greska pri otvaranju fajla";
      exit(1);
    }
    text = std::string((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    // std::string contents((std::istreambuf_iterator<char>(file)),
    //                      std::istreambuf_iterator<char>());
    // text = std::move(contents);
  }
  std::string key = argv[4];
  std::string result = "";

  switch (decision) {
  case CKSUM_CAESAR: {
    int shift = 0;
    try {
      shift = std::stoi(key);
    } catch (...) {
      std::cerr << "Shift vrednost za caesar sifru nije validna.\n";
      printUsage(argv[0]);
      exit(1);
    }

    if (action == ENC)
      result = caeserEncrypt(text, shift);
    else
      result = caeserDecrypt(text, shift);
    break;
  }
  case CKSUM_VIGENERE: {
    if (action == ENC)
      result = vigenereEncrypt(text, key);
    else
      result = vigenereDecrypt(text, key);
    break;
  }
  case CKSUM_HEBERN: {
    if (action == ENC)
      result = hebernEncrypt(text, key);
    else
      result = hebernDecrypt(text, key);
    break;
  }
  }

  std::cout << result << "\n";
  exit(0);
}

constexpr uint16_t MAX = std::numeric_limits<uint16_t>::max();

[[gnu::noreturn]]
void interactive() {
  std::cout << "Interaktivan rezim:\n";
  while (true) {
    std::cout << "Izaberite sifru:\n"
              << "1. Caesar\n"
              << "2. Vigenerer\n"
              << "3. Hebern\n"
              << "0. Izlaz\n"
              << "Izbor: ";
    uint16_t decision;
    std::cin >> decision;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (decision == 0) {
      std::cout << "Izlazimo...\n";
      exit(0);
    }
    if (decision > 3) {
      std::cout << "Postoje samo opcije 1, 2  i 3.\n";
      continue;
    }

    std::cout << "Izaberite:\n"
              << "1. Enkriptujte\n"
              << "2. Dekriptujte\n"
              << "Izbor: ";
    std::string action_str;
    std::cin >> action_str;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (action_str != "1" && action_str != "2") {
      std::cerr << "Postoje samo opcije 1 i 2.\n";
      continue;
    }
    bool action = action_str == "1" ? true : false;

    std::string text;
    std::cout << "Unesite tekst: ";
    std::getline(std::cin, text);

    std::string result = "";

    switch (decision) {
    case 1: {
      int shift;
      std::cout << "Unesite shift (broj): ";
      std::cin >> shift;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if (action)
        result = caeserEncrypt(text, shift);
      else
        result = caeserDecrypt(text, shift);
      break;
    }
    case 2: {
      std::string key;
      std::cout << "Unesite kljuc (string): ";
      std::getline(std::cin, key);

      if (action)
        result = vigenereEncrypt(text, key);
      else
        result = vigenereDecrypt(text, key);

      break;
    }
    case 3: {
      std::string rotor;
      std::cout << "Unesite rotor (string): ";
      std::getline(std::cin, rotor);

      if (action)
        result = hebernEncrypt(text, rotor);
      else
        result = hebernDecrypt(text, rotor);

      break;
    }
    // vec je provereno ali za svaki slucaj
    default:
      std::cout << "Postoje sifre 1, 2 i 3.\n";
      continue;
    }

    if (!result.empty())
      std::cout << "Rezultat:\n" << result << "\n\n";
  }
}
