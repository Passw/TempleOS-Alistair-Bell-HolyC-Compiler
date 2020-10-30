project(Improved-C-SDK)

set(SDK_SOURCES
    Common.h
    SDK.h

    Tokens.h

    Lexer.h
    Lexer.c

    Stream.h
    Stream.c

    Tests.h
    Tests.c
)

add_library(${PROJECT_NAME} STATIC ${SDK_SOURCES})