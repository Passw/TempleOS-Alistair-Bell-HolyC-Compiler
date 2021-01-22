#!/bin/bash
clear

cmake -B Build -D PROJECT_BUILD_TESTS=On -D CMAKE_BUILD_TYPE=Debug
if [ $? != 0 ]; then
    echo "CMake generated errors - refusing to make"
fi

./GenerateCompileCommands.sh

cd Build 

# Build everything
make

# Run unit tests
make test

cd ../


./Build/HolyC-Tools/Compiler/HolyC-Compiler $1
