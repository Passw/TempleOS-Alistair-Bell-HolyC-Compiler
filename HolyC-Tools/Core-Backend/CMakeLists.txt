project(Core-Backend)

set(BACKEND_SOURCES
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
add_library(${PROJECT_NAME} SHARED ${BACKEND_SOURCES})
