#!/bin/bash
clear

# Get the user architecture
arch=$(uname -m)

cmake -B Build \
    -D CMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -D PROJECT_BUILD_TESTS=On \
    -D CMAKE_BUILD_TYPE=Debug \
    -D PROJECT_BUILD_ARCHITECTURE=$arch

cd Build
# Run unit tests
make && make test
mv compile_commands.json ../
cd ../

