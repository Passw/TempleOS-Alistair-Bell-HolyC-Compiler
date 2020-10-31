#ifndef TOKENS_HEADER
#define TOKENS_HEADER

#include "Common.h"


typedef struct IC_Lexer IC_Lexer;

typedef enum IC_LEXICAL_TOKENS_ENUM
{
    IC_LEXICAL_TOKENS_INVALID = -1,
    
    IC_LEXICAL_TOKENS_SEMI_COLON,

    /*
        Operators
    */  
    IC_LEXICAL_TOKENS_PLUS,
    IC_LEXICAL_TOKENS_MINUS,
    IC_LEXICAL_TOKENS_MULTIPLY,
    IC_LEXICAL_TOKENS_DIVIDE,
    IC_LEXICAL_TOKENS_EQUALS,   
    
    /*
        Keywords
    */
    IC_LEXICAL_TOKENS_FOR,
    IC_LEXICAL_TOKENS_WHILE,

    /* 
        Predefined types
    */
    IC_LEXICAL_TOKENS_I8,
    IC_LEXICAL_TOKENS_U0,
    IC_LEXICAL_TOKENS_U8,
    IC_LEXICAL_TOKENS_I16,
    IC_LEXICAL_TOKENS_U16,
    IC_LEXICAL_TOKENS_I32,
    IC_LEXICAL_TOKENS_U32,
    IC_LEXICAL_TOKENS_I64,
    IC_LEXICAL_TOKENS_U64,
    IC_LEXICAL_TOKENS_F32,
    IC_LEXICAL_TOKENS_F64,
} IC_LexicalTokens;

typedef struct IC_Token
{
    IC_LexicalTokens    Token;
    I32                 ReferenceLine;
    I32                 ReferenceLineIndex;
} IC_Token;

extern U8 IC_TokenFromString(IC_Lexer *lexer, IC_Token *token, const I8 *source);


#endif