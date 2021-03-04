cmake_minimum_required(VERSION 3.5)
project(HolyC)

option(PROJECT_BUILD_TESTS "Build the test programs" Off)
option(PROJECT_BUILD_ARCHITECTURE "SDK target architecutre" Off)
enable_language(ASM-ATT)


# common flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror")

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "Building in release mode, optimisations set, debug symbols stripped")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2") # O3 is dangerous
else()
    message(STATUS "Building in debug mode")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
endif()

Message(STATUS "SDK architecutre ${PROJECT_BUILD_ARCHITECTURE}")

add_subdirectory(HolyC-Tools/Compiler) # Compiler
add_subdirectory(HolyC-Tools/Disassembler) # Dissasembler
add_subdirectory(HolyC-Tools/Linker) # Linker
add_subdirectory(HolyC-Tools/Core-Backend) # Interface library for common stuff

if (PROJECT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(HolyC-Tools/Tests)
endif(PROJECT_BUILD_TESTS)
