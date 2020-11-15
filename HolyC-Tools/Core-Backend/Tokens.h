#ifndef TOKENS_HEADER
#define TOKENS_HEADER

#include "Common.h"

#define HC_TOKEN_SOURCE_MAX_BUFFER_COUNT 255

typedef struct HC_Lexer HC_Lexer;

typedef enum HC_LEXICAL_TOKENS_ENUM
{
    HC_LEXICAL_TOKENS_SEMI_COLON,

    /*
        Operators
    */  
    HC_LEXICAL_TOKENS_PLUS,
    HC_LEXICAL_TOKENS_MINUS,
    HC_LEXICAL_TOKENS_MULTIPLY,
    HC_LEXICAL_TOKENS_DIVIDE,
    HC_LEXICAL_TOKENS_EQUALS,  

    HC_LEXICAL_TOKENS_LEFT_PARAM,
    HC_LEXICAL_TOKENS_RIGHT_PARAM,

    HC_LEXICAL_TOKENS_LEFT_CURLY_BRACKET,
    HC_LEXICAL_TOKENS_RIGHT_CURLY_BRACKET,

    HC_LEXICAL_TOKENS_STARTING_COMMENT,
    HC_LEXICAL_TOKENS_ENDING_COMMENT,
    
    HC_LEXICAL_TOKENS_SINGLE_QUOTE,
    HC_LEXICAL_TOKENS_DOUBLE_QUOTE,

    HC_LEXICAL_TOKENS_VALUE,

    HC_LEXICAL_TOKENS_NEW_SYMBOL,

    /*
        Keywords
    */
    HC_LEXICAL_TOKENS_FOR,
    HC_LEXICAL_TOKENS_WHILE,

    /* 
        Predefined types
    */
    HC_LEXICAL_TOKENS_I8,
    HC_LEXICAL_TOKENS_U0,
    HC_LEXICAL_TOKENS_U8,
    HC_LEXICAL_TOKENS_I16,
    HC_LEXICAL_TOKENS_U16,
    HC_LEXICAL_TOKENS_I32,
    HC_LEXICAL_TOKENS_U32,
    HC_LEXICAL_TOKENS_I64,
    HC_LEXICAL_TOKENS_U64,
    HC_LEXICAL_TOKENS_F32,
    HC_LEXICAL_TOKENS_F64,
} HC_LexicalTokens;

typedef struct HC_Token
{
    HC_LexicalTokens    Token;
    U64                 Hash;
    I8                  Source[HC_TOKEN_SOURCE_MAX_BUFFER_COUNT];
} HC_Token;
typedef struct HC_TokenHandleInfo
{
    HC_Lexer            *Lexer;
    HC_Token            *PreviousToken;
    I8                  Source[HC_TOKEN_SOURCE_MAX_BUFFER_COUNT];
    U64                 SourceLength;
} HC_TokenHandleInfo;

extern U64 HC_TokenHashString(const I8 *source);
extern U64 HC_TokenHashChar(const I8 character);
extern U8 HC_TokenCreate(HC_Token *token, HC_TokenHandleInfo *info);

#endif