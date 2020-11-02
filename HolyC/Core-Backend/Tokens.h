#ifndef TOKENS_HEADER
#define TOKENS_HEADER

#include "Common.h"


typedef struct HC_Lexer HC_Lexer;

typedef enum HC_LEXICAL_TOKENS_ENUM
{
    HC_LEXICAL_TOKENS_INVALID = -1,
    
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

    HC_LEXICAL_TOKENS_LEFT_CURLY,
    HC_LEXICAL_TOKENS_RIGHT_CURLY,

    HC_LEXICAL_TOKENS_LEFT_CURLY_BRACKET,
    HC_LEXICAL_TOKENS_RIGHT_CURLY_BRACKET,
    
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
    I32                 ReferenceLine;
    I32                 ReferenceLineIndex;
    U64                 Hash;
    const I8            *Source;
} HC_Token;

extern U8 HC_TokenFromString(HC_Lexer *lexer, HC_Token *token, const I8 *source);
extern U8 HC_TokenCheckSingleChar(HC_Lexer *lexer, HC_Token *token, const I8 character);
extern U8 HC_TokenCheckGrammer(HC_Lexer *lexer, HC_Token *token, const I8 *source);

#endif