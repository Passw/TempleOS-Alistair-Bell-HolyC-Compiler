#!/bin/bash
clear
cmake -B Build -D PROJECT_BUILD_TESTS=ON -D CMAKE_BUILD_TYPE=Debug
cd Build && make
cd ../

./Build/HolyC-Tools/Tests/Test-Tests
./Build/HolyC-Tools/Tests/Test-Tokens
./Build/HolyC-Tools/Tests/Test-HelloWorld