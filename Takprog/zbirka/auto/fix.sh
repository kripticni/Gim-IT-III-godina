#!/usr/bin/env bash
out=$(basename $1 | xargs -I {} echo bin/{} | awk -F'.' '{print $1}')
g++ "$1" -O2 -o "$out"
