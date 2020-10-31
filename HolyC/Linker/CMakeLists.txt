project(HolyC-Linker)

set(LINKER_SOURCES
    Linker.c
)

add_executable(${PROJECT_NAME} ${LINKER_SOURCES})