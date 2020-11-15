#!/bin/bash
clear
cmake -B Build -D PROJECT_BUILD_TESTS=ON -D CMAKE_BUILD_TYPE=Debug
cd Build && make
cd ../

./Build/HolyC-Tools/Compiler/HolyC-Compiler $1