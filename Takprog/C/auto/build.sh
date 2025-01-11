#!/usr/bin/env bash
out=$(echo "bin/$1" | awk -F'.' '{print $1}')
g++ "$1" -O2 -o "$out"
mv "$1" src/
