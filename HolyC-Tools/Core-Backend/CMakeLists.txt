project(Core-Backend)

set(SDK_SOURCES
    Common.h
    SDK.h

    Tokens.h
    Tokens.c

    Lexer.h
    Lexer.c
    
    Tokens.h

    Analyser.h
    Analyser.c

    Stream.h
    Stream.c
    
    Tests.h
    Tests.c
)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror") # With any legacy api the syntax is terrible, holyc is divine and clean
add_library(${PROJECT_NAME} STATIC ${SDK_SOURCES})