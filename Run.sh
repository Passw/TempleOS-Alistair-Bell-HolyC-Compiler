#!/bin/bash
cmake -B Build -D PROJECT_BUILD_TESTS=ON
cd Build && make
cd ../

./Build/Improved-C/Compiler/Improved-C-Compiler $1