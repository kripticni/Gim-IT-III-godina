#ifndef KRYPTOS_HPP
#define KRYPTOS_HPP
#include <string>

// cezarova sifra
std::string caeserEncrypt(const std::string &, int);
std::string caeserDecrypt(const std::string &, int);

// vigenere sifra
std::string vigenereEncrypt(const std::string &, const std::string &);
std::string vigenereDecrypt(const std::string &, const std::string &);

// hebernova
std::string hebernEncrypt(const std::string &, std::string);
std::string hebernDecrypt(const std::string &, std::string);

// enigma implementacija na
// https://github.com/gsiddhad/Cryptography/tree/master/Enigma%20Machine

#endif // KRYPTOS_HPP
