#ifndef TOKENS_HEADER
#define TOKENS_HEADER

#include "Common.h"

typedef enum IC_LEXICAL_TOKENS_ENUM
{
    IC_LEXICAL_TOKENS_INVALID = -1,

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
} IC_LexicalTokens;

typedef struct
{
    const I8            *ReferenceFile;
    IC_LexicalTokens    Token;
    I32                 ReferenceLine;
    I32                 ReferenceLineIndex;
} IC_Token;


#endif