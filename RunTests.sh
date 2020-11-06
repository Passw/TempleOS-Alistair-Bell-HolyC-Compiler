#!/bin/bash
clear
cmake -B Build -D PROJECT_BUILD_TESTS=ON -D CMAKE_BUILD_TYPE=Debug
cd Build && make
cd ../

./Build/HolyC/Tests/Test-Tests
./Build/HolyC/Tests/Test-Tokens
./Build/HolyC/Tests/Test-Nasm-Assembler