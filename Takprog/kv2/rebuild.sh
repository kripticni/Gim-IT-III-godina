#!/usr/bin/env bash
ls src | xargs -I {} g++ "src/{}" -O2 -o "bin/$(basename {} .cpp)"
