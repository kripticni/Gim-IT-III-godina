#!/usr/bin/env bash

cat Kryptos.md SSL-Uvod.md GimCTF.md >pandoc.md
pandoc pandoc.md -o ../pandoc.pptx
