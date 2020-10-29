project(Improved-C-Compiler)

set(COMPILER_SOURCES
    Main.c
)
include_directories(../)

add_executable(${PROJECT_NAME} ${COMPILER_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC Improved-C-SDK)