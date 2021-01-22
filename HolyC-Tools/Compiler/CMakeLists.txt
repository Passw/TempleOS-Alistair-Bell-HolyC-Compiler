project(HolyC-Compiler)

set(COMPILER_SOURCES
    Compiler.c
    Compiler.h
    CompilerMain.c
)
include_directories(../)

add_executable(${PROJECT_NAME} ${COMPILER_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC Core-Backend)
