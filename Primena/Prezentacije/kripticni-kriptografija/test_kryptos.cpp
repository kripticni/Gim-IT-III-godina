#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "kryptos.hpp"
#include <string>

TEST_CASE("Caesar cipher encryption", "[caesar]") {
  REQUIRE(caeserEncrypt("HELLO", 3) == "KHOOR");
  REQUIRE(caeserEncrypt("abc", 1) == "bcd");
  REQUIRE(caeserEncrypt("xyz", 2) == "zab");
  REQUIRE(caeserEncrypt("Hello, World!", 5) == "Mjqqt, Btwqi!");
}

TEST_CASE("Caesar cipher decryption", "[caesar]") {
  REQUIRE(caeserDecrypt("KHOOR", 3) == "HELLO");
  REQUIRE(caeserDecrypt("bcd", 1) == "abc");
  REQUIRE(caeserDecrypt("zab", 2) == "xyz");
  REQUIRE(caeserDecrypt("Mjqqt, Btwqi!", 5) == "Hello, World!");
}

TEST_CASE("Vigenère cipher encryption", "[vigenere]") {
  REQUIRE(vigenereEncrypt("HELLO", "KEY") == "RIJVS");
  REQUIRE(vigenereEncrypt("attackatdawn", "lemon") == "lxfopvefrnhr");
  REQUIRE(vigenereEncrypt("Hello, World!", "KEY") == "Rijvs, Uyvjn!");
}

TEST_CASE("Vigenère cipher decryption", "[vigenere]") {
  REQUIRE(vigenereDecrypt("RIJVS", "KEY") == "HELLO");
  REQUIRE(vigenereDecrypt("lxfopvefrnhr", "lemon") == "attackatdawn");
  REQUIRE(vigenereDecrypt("Rijvs, Uyvjn!", "KEY") == "Hello, World!");
}

TEST_CASE("Hebern cipher encryption and decryption", "[hebern]") {
  std::string rotor =
      "phqgiumeaylnofdxjkrcvstzwb"; // A valid 26-char permutation

  std::string plaintext = "hello";
  std::string encrypted = hebernEncrypt(plaintext, rotor);
  std::string decrypted = hebernDecrypt(encrypted, rotor);

  REQUIRE(decrypted == plaintext);

  plaintext = "HELLO WORLD";
  encrypted = hebernEncrypt(plaintext, rotor);
  decrypted = hebernDecrypt(encrypted, rotor);

  REQUIRE(decrypted == plaintext);
}
