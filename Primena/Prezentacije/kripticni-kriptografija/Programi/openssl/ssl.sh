#!/usr/bin/env bash

source quickssl.sh

menu() {
  echo "=== OpenSSL Funkcije ==="
  echo "1) AES Enkriptuj"
  echo "2) AES Dekriptuj"
  echo "3) Generisi RSA par kljuceva"
  echo "4) Ekstraktuj RSA javni kljuc"
  echo "5) RSA Enkriptuj"
  echo "6) RSA Dekriptuj"
  echo "7) Generisi DSA parametre"
  echo "8) Generisi DSA kljuc"
  echo "9) DSA Podpisi"
  echo "10) DSA Verifikuj"
  echo "11) Generisi EC kljuc"
  echo "12) Ekstraktuj EC javni kljuc"
  echo "13) Generisi DH parametre"
  echo "14) SHA256 Hash-uj"
  echo "15) SHA512 Hash-uj"
  echo "16) MD5 Hash-uj"
  echo "17) Base64 Enkodiraj"
  echo "18) Base64 Dekodiraj"
  echo "19) Generisi nasumican hex"
  echo "0) Izlaz"
  echo "=========================="
}

while true; do
  menu
  read -rp "Izaberite opciju: " opt
  case $opt in
  1)
    read -rp "Ulazni fajl: " in
    read -rp "Izlazni fajl: " out
    encrypt_aes "$in" "$out"
    ;;
  2)
    read -rp "Ulazni fajl: " in
    read -rp "Izlazni fajl: " out
    decrypt_aes "$in" "$out"
    ;;
  3) gen_rsa_key ;;
  4) extract_rsa_pub ;;
  5)
    read -rp "Ulazni fajl: " in
    read -rp "Izlazni fajl: " out
    encrypt_rsa "$in" "$out"
    ;;
  6)
    read -rp "Ulazni fajl: " in
    read -rp "Izlazni fajl: " out
    decrypt_rsa "$in" "$out"
    ;;
  7) gen_dsa_params ;;
  8) gen_dsa_keys ;;
  9)
    read -rp "Ulazni fajl za potpisivanje: " in
    read -rp "Potpisan izlazni fajl: " out
    sign_dsa "$in" "$out"
    ;;
  10)
    read -rp "Originalni fajl: " in
    read -rp "Potpisan fajl: " sig
    verify_dsa "$in" "$sig"
    ;;
  11) gen_ec_key ;;
  12) extract_ec_pub ;;
  13) gen_dh_params ;;
  14)
    read -rp "Fajl za hash: " file
    sha256 "$file"
    ;;
  15)
    read -rp "Fajl za hash: " file
    sha512 "$file"
    ;;
  16)
    read -rp "Fajl za hash: " file
    md5 "$file"
    ;;
  17)
    read -rp "Ulazni fajl: " in
    read -rp "Izlazni fajl: " out
    b64_encode "$in" "$out"
    ;;
  18)
    read -rp "Ulazni fajl: " in
    read -rp "Izlazni fajl: " out
    b64_decode "$in" "$out"
    ;;
  19)
    read -rp "Broj byte-ova: " bytes
    rand_hex "$bytes"
    ;;
  0)
    break
    ;;
  *) echo "Opcija nije validna." ;;
  esac
  echo ""
done
