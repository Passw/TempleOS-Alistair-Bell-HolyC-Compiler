project(Core-Backend)

set(BACKEND_SOURCES SHARED
    Common.h
    SDK.h

    Tokens.h
    Tokens.c

    Lexer.h
    Lexer.c
    
    Errors.h
    Errors.c

    Analyser.h
    Analyser.c

    Stream.h
    Stream.c
    
    Tests.h
    Tests.c
)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
add_library(${PROJECT_NAME} STATIC ${BACKEND_SOURCES})
