cmake_minimum_required(VERSION 3.5)
project(Improved-C)

option(PROJECT_BUILD_TESTS "Build the test programs" OFF)

add_subdirectory(Improved-C/Compiler) # Compiler
add_subdirectory(Improved-C/Disassembler) # Dissasembler
add_subdirectory(Improved-C/Linker) # Linker
add_subdirectory(Improved-C/Improved-C-SDK) # Interface library for common stuff

if (PROJECT_BUILD_TESTS)
    add_subdirectory(Improved-C/Tests)
endif(PROJECT_BUILD_TESTS)