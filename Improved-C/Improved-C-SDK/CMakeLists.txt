project(Improved-C-SDK)

add_library(${PROJECT_NAME} STATIC
    Common.h
    SDK.h

    Tokens.h

    Lexer.h
    Lexer.c

    Stream.h
    Stream.c
)