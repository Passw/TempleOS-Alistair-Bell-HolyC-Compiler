project(HolyC-Compiler)

set(COMPILER_SOURCES
    Compiler.c
    Compiler.h
    CompilerMain.c
)
include_directories(../)

if (${PROJECT_TARGET_ARCHITECTURE} STREQUAL "amd64")
    set(COMPILER_SOURCES
        ${COMPILER_SOURCES}
        Amd64/Registers.h
        Amd64/Instructions.h    
    )
endif(${PROJECT_TARGET_ARCHITECTURE} STREQUAL "amd64")

add_executable(${PROJECT_NAME} ${COMPILER_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC Core-Backend)