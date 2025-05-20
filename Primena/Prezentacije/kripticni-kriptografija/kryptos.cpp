#include <cstdint>
#include <string>

std::string caeserEncrypt(const std::string &text, int shift) {
  std::string result = "";
  for (const char &c : text)
    if (isalpha(c)) {
      char base = isupper(c) ? 'A' : 'a';
      result += (c - base + shift) % 26 + base;
    } else
      result += c;
  return result;
}

std::string caeserDecrypt(const std::string &text, int shift) {
  return caeserEncrypt(text, 26 - shift % 26);
}

std::string vigenereEncrypt(const std::string &text, const std::string &key) {
  std::string result = "";
  uint64_t keyLen = key.length();
  for (uint64_t i = 0, j = 0; i < text.length(); ++i) {
    char c = text[i];
    if (isalpha(c)) {
      char base = isupper(c) ? 'A' : 'a';
      char k = tolower(key[j % keyLen]) - 'a';
      result += (c - base + k) % 26 + base;
      ++j;
    } else
      result += c;
  }
  return result;
}

std::string vigenereDecrypt(const std::string &text, const std::string &key) {
  std::string result = "";
  uint64_t keyLen = key.length();
  for (uint64_t i = 0, j = 0; i < text.length(); ++i) {
    char c = text[i];
    if (isalpha(c)) {
      char base = isupper(c) ? 'A' : 'a';
      char k = tolower(key[j % keyLen]) - 'a';
      result += (c - base - k + 26) % 26 + base;
      ++j;
    } else
      result += c;
  }
  return result;
}

std::string hebernEncrypt(const std::string &text, std::string rotor) {
  std::string result = "";
  for (char c : text)
    if (isalpha(c)) {
      char base = isupper(c) ? 'A' : 'a';
      int index = tolower(c) - 'a';
      char encrypted = rotor[index];
      result += isupper(c) ? toupper(encrypted) : encrypted;
      char first = rotor[0];
      rotor = rotor.substr(1) + first;
    } else
      result += c;
  return result;
}

std::string hebernDecrypt(const std::string &text, std::string rotor) {
  std::string result = "";
  for (char c : text)
    if (isalpha(c)) {
      char lower_c = tolower(c);
      int index = rotor.find(lower_c);
      char decrypted = 'a' + index;
      result += isupper(c) ? toupper(decrypted) : decrypted;
      char first = rotor[0];
      rotor = rotor.substr(1) + first;
    } else
      result += c;

  return result;
}
