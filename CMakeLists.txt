cmake_minimum_required(VERSION 3.5)
project(Improved-C)

option(PROJECT_BUILD_TESTS "Build the test programs" OFF)

add_subdirectory(HolyC/Compiler) # Compiler
add_subdirectory(HolyC/Disassembler) # Dissasembler
add_subdirectory(HolyC/Linker) # Linker
add_subdirectory(HolyC/HolyC-SDK) # Interface library for common stuff

if (PROJECT_BUILD_TESTS)
    add_subdirectory(HolyC/Tests)
endif(PROJECT_BUILD_TESTS)