cmake_minimum_required(VERSION 3.5)
project(Improved-C)

enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <FLAGS> <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)


option(PROJECT_BUILD_TESTS "Build the test programs" OFF)

if (NOT "${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    Message(FATAL_ERROR "Platform must be 64 bit")
endif()

EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )

if (${ARCHITECTURE} STREQUAL "x86_64" OR ${ARCHITECTURE} STREQUAL "amd64")
    set(PROJECT_TARGET_ARCHITECTURE "amd64" CACHE INTERNAL "")
else()
    Message(FATAL_ERROR "${ARCHITECTURE} has not been implimented")
endif()

add_subdirectory(HolyC/Compiler) # Compiler
add_subdirectory(HolyC/Disassembler) # Dissasembler
add_subdirectory(HolyC/Linker) # Linker
add_subdirectory(HolyC/Core-Backend) # Interface library for common stuff

if (PROJECT_BUILD_TESTS)
    add_subdirectory(HolyC/Tests)
endif(PROJECT_BUILD_TESTS)