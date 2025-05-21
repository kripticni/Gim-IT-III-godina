#!/usr/bin/env bash

g++ tests/test_kryptos.cpp src/kryptos.cpp -o bin/tests
./bin/tests

g++ -c src/kryptos.cpp -o build/kryptos.o
ar rcs build/libkryptos.a build/kryptos.o
