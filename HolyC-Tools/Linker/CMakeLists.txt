project(HolyC-Linker)

set(LINKER_SOURCES
    Linker.c
)
include_directories(../)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
add_executable(${PROJECT_NAME} ${LINKER_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC Core-Backend)