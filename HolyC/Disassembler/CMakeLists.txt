project(HolyC-Disassembler)

set(DISASSEMBLER_SOURCES
    Disassembler.c
)

add_executable(${PROJECT_NAME} ${DISASSEMBLER_SOURCES})