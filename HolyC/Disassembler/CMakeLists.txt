project(HolyC-Disassembler)

set(DISASSEMBLER_SOURCES
    Disassembler.c
)
include_directories(../)

add_executable(${PROJECT_NAME} ${DISASSEMBLER_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC Core-Backend)