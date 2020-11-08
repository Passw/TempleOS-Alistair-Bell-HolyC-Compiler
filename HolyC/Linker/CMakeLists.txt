project(HolyC-Linker)

set(LINKER_SOURCES
    Linker.c
)
include_directories(../)

add_executable(${PROJECT_NAME} ${LINKER_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC Core-Backend)