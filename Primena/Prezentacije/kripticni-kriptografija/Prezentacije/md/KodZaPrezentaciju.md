# Kryptos biblioteka

# Cezarova Sifra

***

## Enkripcija

```cpp
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
```

***

## Dekripcija

```cpp
std::string caeserDecrypt(const std::string &text, int shift) {
  return caeserEncrypt(text, 26 - shift % 26);
}
```

***

# Vigenere sifra

***

## Enkripcija

```cpp
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
```

***

## Dekripcija

```cpp
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
```

***

# Hebernova masina

***

## Enkripcija

```cpp
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
```

***

## Dekripcija

```cpp
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
```
# OpenSSL

## AES (Simetricna enkripcija)

```bash
encrypt_aes() {
  openssl enc -aes-256-cbc -pbkdf2 -salt -in "$1" -out "$2"
}

decrypt_aes() {
  openssl enc -aes-256-cbc -d -pbkdf2 -in "$1" -out "$2"
}
```

***

## RSA (Asimetricna enkripcija)

### Generisanje

```bash
gen_rsa_key() {
  openssl genpkey -algorithm RSA -out rsa_private.pem -pkeyopt rsa_keygen_bits:2048
}

extract_rsa_pub() {
  openssl rsa -in rsa_private.pem -pubout -out rsa_public.pem
}
```

***

### Enkripcija

```bash
encrypt_rsa() {
  openssl rsautl -encrypt -inkey rsa_public.pem -pubin -in "$1" -out "$2"
}

decrypt_rsa() {
  openssl rsautl -decrypt -inkey rsa_private.pem -in "$1" -out "$2"
}
```

***

## DSA (Digitalan Potpis)

### Generisanje

```bash
gen_dsa_params() {
  openssl dsaparam -out dsa_params.pem 2048
}

gen_dsa_keys() {
  openssl gendsa -out dsa_private.pem dsa_params.pem
  openssl dsa -in dsa_private.pem -pubout -out dsa_public.pem
}
```

***

### Enkripcija

```bash
sign_dsa() {
  openssl dgst -sha256 -sign dsa_private.pem -out "$2" "$1"
}

verify_dsa() {
  openssl dgst -sha256 -verify dsa_public.pem -signature "$2" "$1"
}
```

***

## ECC (Eklipticka Kriva)

```bash
gen_ec_key() {
  openssl ecparam -name prime256v1 -genkey -noout -out ec_private.pem
}

extract_ec_pub() {
  openssl ec -in ec_private.pem -pubout -out ec_public.pem
}
```

***

## Diffie-Hellman (Razmena Kljuceva)

```bash
gen_dh_params() {
  openssl dhparam -out dh_params.pem 2048
}

# Samo pravi DH parametre
# Sama razmena se vrsi unutra aplikacija
```

***

## Hashing Functions (SHA, MD5) (Nepovratne funkcije) 

```bash
sha256() {
  openssl dgst -sha256 "$1"
}

sha512() {
  openssl dgst -sha512 "$1"
}

md5() {
  openssl dgst -md5 "$1"
}
```

***

## Base64 (Enkodiranje i Dekodiranje)

```bash
b64_encode() {
  openssl base64 -in "$1" -out "$2"
}

b64_decode() {
  openssl base64 -d -in "$1" -out "$2"
}
```

***

## Generisanje nasumicnih bitova

```bash
rand_hex() {
  openssl rand -hex "$1"
}
```

***
