project(HolyC-SDK)

set(SDK_SOURCES
    Common.h
    SDK.h

    Tokens.h
    Tokens.c

    Lexer.h
    Lexer.c

    Stream.h
    Stream.c

    Tests.h
    Tests.c
)

add_library(${PROJECT_NAME} STATIC ${SDK_SOURCES})