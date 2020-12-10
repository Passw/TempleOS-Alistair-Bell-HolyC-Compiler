cmake_minimum_required(VERSION 3.5)
project(HolyC)

option(PROJECT_BUILD_TESTS "Build the test programs" OFF)

if (NOT "${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    Message(FATAL_ERROR "Platform must be 64 bit")
endif()

enable_language(ASM-ATT)


EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )

if (${ARCHITECTURE} STREQUAL "x86_64" OR ${ARCHITECTURE} STREQUAL "amd64")
    set(PROJECT_TARGET_ARCHITECTURE "amd64" CACHE INTERNAL "")
else()
    Message(FATAL_ERROR "${ARCHITECTURE} has not been implimented")
endif()

# common flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall")

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "Building in release mode, optimisations set, debug symbols stripped")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2") # O3 is dangerous

else()
    message(STATUS "Building in debug mode")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
endif()


add_subdirectory(HolyC-Tools/Compiler) # Compiler
add_subdirectory(HolyC-Tools/Disassembler) # Dissasembler
add_subdirectory(HolyC-Tools/Linker) # Linker
add_subdirectory(HolyC-Tools/Core-Backend) # Interface library for common stuff
add_subdirectory(HolyC-SDK) # Tools to write HolyC code :)

if (PROJECT_BUILD_TESTS)
    add_subdirectory(HolyC-Tools/Tests)
endif(PROJECT_BUILD_TESTS)