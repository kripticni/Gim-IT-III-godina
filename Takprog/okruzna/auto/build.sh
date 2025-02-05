#!/usr/bin/env bash
out=$(echo "bin/$1" | awk -F'.' '{print $1}')
g++ "$1" -O2 -o "$out" -std=c++14 -Wall -Wextra
mv "$1" src/
