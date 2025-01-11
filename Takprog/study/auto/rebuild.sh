#!/usr/bin/env bash
rm -f ./bin/*
for file in src/*.cpp; do
  output="bin/$(basename "$file" | awk -F'.' '{print $1}')"
  g++ "$file" -O2 -o "$output" -std=c++14 -Wall -Wextra
done
